#include "cone.h"

#include <cmath>
#include "bounding_sphere.h"

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

Cone::Cone(const Vector3<double> &normal, const Point3<double> &center,
           double length, double radius)
{
    if (!normal || FLT_EPSILON > length || FLT_EPSILON > radius)
        throw CALL_EX(DegenerateConeException);

    this->normal = std::make_shared<Vector3<double>>(normal.normalised());
    this->length = length / 2;
    this->center = std::make_shared<Point3<double>>(center + *this->normal * (-this->length));
    this->radius = radius;
    this->rsqr = radius * radius;
    this->lsqr = length * length;

    this->cap = std::make_shared<Disk>(center + *this->normal * (-this->length),
                                       -*this->normal, radius);

    this->bounding = std::make_shared<BoundingSphere>(center);

    double r = sqrt(this->length * this->length + radius * radius);

    this->bounding->expand(center + (*this->normal) * r);
    this->bounding->expand(center + (*this->normal) * (-r));

    this->sampler = std::make_shared<CompositeSampler>();
    this->cone_sampler = std::make_shared<ConeSampler>(normal, center, length, radius);

    this->sampler->append(this->cone_sampler.get());
    this->sampler->append(&this->cap->getSampler());
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

    Intersection out = this->coneIntersect(tmp);
    Intersection icap = this->cap->intersect(tmp);

    if (icap && (!out || out.getT() > icap.getT()))
        out = Intersection(this, icap.getPoint(), icap.getNormal(), icap.getT(),
                           *this->transform_global);

    return out;
}

Intersection Cone::coneIntersect(const Ray3<double> &ray) const
{
    Intersection out;

    Vector3<double> OB = ray.getOrigin() < *this->center;
    double nn = 1 / (*this->normal & *this->normal),
           vn = ray.getDirection() & *this->normal,
           nOB = *this->normal & OB;
    Vector3<double> a = ray.getDirection() \
                        - vn * nn * *this->normal,
                    b = OB - nOB * nn * *this->normal;
    double c = vn * nn, d = nOB * nn;
    double rrhh = this->rsqr / this->lsqr;
    double dh = d - 2 * this->length;

    double aa = a & a, bb = b & b, ab = a & b;

    tools::sqr_eq_res_t res = tools::solve_sqr(aa - c * c * rrhh,
                                               2 * (ab - c * dh * rrhh),
                                               bb - rrhh * dh * dh);
    double t = -1, k;

    for (int i = 0; res.n > i; i++)
    {
        k = c * res.x[i] + d;

        if (res.x[i] > FLT_EPSILON && 2 * this->length + FLT_EPSILON > k
            && FLT_EPSILON < k
            && (0 > t || t > res.x[i]))
            t = res.x[i];
    }

    if (0 > t)
        return out;

    Point3<double> point = ray(t);
    Point3<double> top = *this->center + *this->normal * 2 * this->length;
    Vector3<double> sidev = top > point;
    Point3<double> side = top + 2 * this->length \
                                * (sidev & (-*this->normal)) / (sidev & sidev) \
                                * sidev;

    out = Intersection(this, point,
                       Normal3<double>((*this->center > side).normalised()),
                       t, *this->transform_global);

    return out;
}

void Cone::apply(const Transform<double, 3> &transform)
{
    this->normal->apply(transform);
    this->center->apply(transform);
    this->bounding->apply(transform);
    this->cap->apply(transform);
    this->cone_sampler->apply(transform);
}

void Cone::undo(const Transform<double, 3> &transform)
{
    this->normal->undo(transform);
    this->center->undo(transform);
    this->bounding->undo(transform);
    this->cap->undo(transform);
    this->cone_sampler->undo(transform);
}

