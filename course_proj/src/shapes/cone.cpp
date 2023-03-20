#include "cone.h"

#include <cmath>
#include "bounding_sphere.h"

#include "transform_strategies.h"

#include "composite_sampler.h"
#include "cone_sampler.h"

#include "tools.h"

const Attribute &Cone::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Cone::MAXATTR,
                                              {Cone::ATTRI});
    return attr;
}

Cone::Cone(double length, double radius)
{
    if (FLT_EPSILON > length || FLT_EPSILON > radius)
        throw CALL_EX(DegenerateConeException);

    this->length = length / 2;
    this->radius = radius;
    this->rsqr = radius * radius;
    this->lsqr = length * length;

    Point3<double> center;
    Vector3<double> normal;

    Transform<double, 3> trans;
    trans.accept(RotateStrategyOZ<double>(M_PI));
    trans.accept(MoveStrategy<double, 3>({0, -this->length, 0}));

    this->cap = std::make_shared<Disk>(radius);
    this->cap->apply(trans);

    this->bounding = std::make_shared<BoundingSphere>(center);

    double r = sqrt(this->length * this->length + radius * radius);

    this->bounding->expand(center + normal * r);
    this->bounding->expand(center + normal * (-r));

    this->sampler = std::make_shared<CompositeSampler>();
    this->cone_sampler = std::make_shared<ConeSampler>(length, radius);

    this->sampler->append(this->cone_sampler.get());
    this->sampler->append(&this->cap->getSampler());

    this->transform_local = std::make_shared<Transform<double, 3>>();
}

Cone::~Cone() {}

const Attribute &Cone::getAttribute(void) const
{
    return Cone::ATTRIBUTE();
}

bool Cone::intersectBounding(const Ray3<double> &ray) const
{
    Ray3<double> tmp = ray;
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    return this->bounding->intersect(tmp);
}

double Cone::area(void) const
{
    return M_PI * this->radius \
           * sqrt(this->rsqr + this->lsqr) + this->cap->area();
}

const ShapeSampler &Cone::getSampler(void) const
{
    return *this->sampler;
}

Intersection Cone::intersect(const Ray3<double> &ray) const
{
    Ray3<double> tmp = ray;
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    Intersection icap = this->cap->intersect(tmp);
    Intersection out = this->coneIntersect(tmp);

    if (icap && (!out || out.getT() > icap.getT()))
    {
        Point3<double> tpoint = icap.getPoint();;
        Normal3<double> tnormal = icap.getNormal();

        tpoint.apply(icap.toGlobal());
        tnormal.apply(icap.toGlobal());

        out = Intersection(this, tpoint, icap.getPointUV(), tnormal,
                           icap.getT(), Transform<double, 3>());
    }

    if (out)
        out = Intersection(this, out.getPoint(), out.getPointUV(),
                           out.getNormal(), out.getT(),
                           *transform_local + *transform_global);

    return out;
}

Intersection Cone::coneIntersect(const Ray3<double> &ray) const
{
    Intersection out;
    Point3<double> center ({0, -this->length, 0});
    Vector3<double> direction ({0, 1, 0});

    Vector3<double> OB = ray.getOrigin() < center;
    double vn = ray.getDirection().y, nOB = OB.y;
    Vector3<double> a = ray.getDirection() - vn * direction,
                    b = OB - nOB * direction;
    double rrhh = this->rsqr / this->lsqr;
    double dh = nOB - 2 * this->length;

    double aa = a & a, bb = b & b, ab = a & b;

    tools::sqr_eq_res_t res = tools::solve_sqr(aa - vn * vn * rrhh,
                                               2 * (ab - vn * dh * rrhh),
                                               bb - rrhh * dh * dh);
    double t = -1, k;

    for (int i = 0; res.n > i; i++)
    {
        double rayk = vn * res.x[i] + nOB;

        if (res.x[i] > FLT_EPSILON && 2 * this->length + FLT_EPSILON > rayk
            && FLT_EPSILON < rayk
            && (0 > t || t > res.x[i]))
        {
            k = rayk;
            t = res.x[i];
        }
    }

    if (0 > t)
        return out;

    Point3<double> point = ray(t);
    Point3<double> top = center + direction * 2 * this->length;
    Vector3<double> sidev = top > point;
    Point3<double> side = top + (-2 * this->length) \
                                * sidev.y / (sidev & sidev) \
                                * sidev;

    Vector3<double> normal = (center > side).normalised();
    double u = ((normal.x > -FLT_EPSILON) ? acos(normal.z) : 2 * M_PI - acos(normal.z)) \
               / (2 * M_PI);
    double v = k / (2 * this->length);

    out = Intersection(this, point, Point2<double>({u, v}),
                       Normal3<double>(normal),
                       t, Transform<double, 3>());

    return out;
}

void Cone::apply(const Transform<double, 3> &transform)
{
    *this->transform_local += transform;
    this->sampler->apply(transform);
}

void Cone::undo(const Transform<double, 3> &transform)
{
    *this->transform_local += transform.inversed();
    this->sampler->undo(transform);
}

