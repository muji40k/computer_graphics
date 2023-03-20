#include "tube.h"

#include <cmath>
#include "bounding_sphere.h"

#include "tube_sampler.h"

#include "tools.h"

const Attribute &Tube::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Tube::MAXATTR,
                                              {Tube::ATTRI});
    return attr;
}

Tube::Tube(double length, double radius)
{
    if (FLT_EPSILON > length || FLT_EPSILON > radius)
        throw CALL_EX(DegenerateTubeException);

    this->length = length / 2;
    this->radius = radius;
    this->rsqr = radius * radius;
    Point3<double> center;
    Vector3<double> normal;

    this->bounding = std::make_shared<BoundingSphere>(center);

    double r = sqrt(this->length * this->length + radius * radius);

    this->bounding->expand(center + normal * r);
    this->bounding->expand(center + normal * (-r));

    this->sampler = std::make_shared<TubeSampler>(length, radius);
    this->transform_local = std::make_shared<Transform<double, 3>>();
}

Tube::~Tube() {}

const Attribute &Tube::getAttribute(void) const
{
    return Tube::ATTRIBUTE();
}

bool Tube::intersectBounding(const Ray3<double> &ray) const
{
    Ray3<double> tmp = ray;
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

    return this->bounding->intersect(tmp);
}

double Tube::area(void) const { return 4 * M_PI * this->radius * this->length; }

const ShapeSampler &Tube::getSampler(void) const
{
    return *this->sampler;
}

Intersection Tube::intersect(const Ray3<double> &ray) const
{
    Ray3<double> tmp = ray;
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);
    Intersection out;
    Point3<double> center;
    Vector3<double> direction ({0, 1, 0});

    Vector3<double> OB = tmp.getOrigin() < center;
    double vn = tmp.getDirection().y,
           nOB = OB.y;
    Vector3<double> a = tmp.getDirection() - vn * direction,
                    b = OB - nOB * direction;

    double aa = a & a, bb = b & b, ab = a & b;

    tools::sqr_eq_res_t res = tools::solve_sqr(aa, 2 * ab, bb - this->rsqr);
    double t = -1, k, tmpk;

    for (int i = 0; res.n > i; i++)
    {
        tmpk = vn * res.x[i] + nOB;

        if (res.x[i] > FLT_EPSILON && this->length + FLT_EPSILON > abs(tmpk)
            && (0 > t || t > res.x[i]))
        {
            t = res.x[i];
            k = tmpk;
        }
    }

    if (0 > t)
        return out;

    Point3<double> point = tmp(t);
    Point3<double> axis = center + direction * k;
    Vector3<double> normal = (axis > point).normalised();

    double u = ((normal.x > -FLT_EPSILON) ? acos(normal.z) : 2 * M_PI - acos(normal.z)) \
               / (2 * M_PI);
    double v = (this->length + k) / (2 * this->length);

    out = Intersection(this, point, Point2<double>(u, v),
                       Normal3<double>(normal), t,
                       *this->transform_local + *this->transform_global);

    return out;
}

void Tube::apply(const Transform<double, 3> &transform)
{
    *this->transform_local += transform;
    this->sampler->apply(transform);
}

void Tube::undo(const Transform<double, 3> &transform)
{
    *this->transform_local += transform.inversed();
    this->sampler->undo(transform);
}

