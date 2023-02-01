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

Tube::Tube(const Vector3<double> &normal, const Point3<double> &center,
           double length, double radius)
{
    if (!normal || FLT_EPSILON > length || FLT_EPSILON > radius)
        throw CALL_EX(DegenerateTubeException);

    this->normal = std::make_shared<Vector3<double>>(normal.normalised());
    this->center = std::make_shared<Point3<double>>(center);
    this->length = length / 2;
    this->radius = radius;
    this->rsqr = radius * radius;

    this->bounding = std::make_shared<BoundingSphere>(*this->center);

    double r = sqrt(this->length * this->length + radius * radius);

    this->bounding->expand(*this->center + (*this->normal) * r);
    this->bounding->expand(*this->center + (*this->normal) * (-r));

    this->sampler = std::make_shared<TubeSampler>(normal, center, length, radius);
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
    Intersection out;

    Vector3<double> OB = tmp.getOrigin() < *this->center;
    double nn = 1 / (*this->normal & *this->normal),
           vn = tmp.getDirection() & *this->normal,
           nOB = *this->normal & OB;
    Vector3<double> a = tmp.getDirection() \
                        - vn * nn * *this->normal,
                    b = OB - nOB * nn * *this->normal;

    double aa = a & a, bb = b & b, ab = a & b;

    tools::sqr_eq_res_t res = tools::solve_sqr(aa, 2 * ab, bb - this->rsqr);
    double t = -1, k, tmpk;

    for (int i = 0; res.n > i; i++)
    {
        tmpk = vn * nn * res.x[i] + nOB * nn;

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
    Point3<double> axis = *this->center + *this->normal * k;

    out = Intersection(this, point,
                       Normal3<double>((axis > point).normalised()),
                       t, *this->transform_global);

    return out;
}

void Tube::apply(const Transform<double, 3> &transform)
{
    this->normal->apply(transform);
    this->center->apply(transform);
    this->bounding->apply(transform);
    this->sampler->apply(transform);
}

void Tube::undo(const Transform<double, 3> &transform)
{
    this->normal->undo(transform);
    this->center->undo(transform);
    this->bounding->undo(transform);
    this->sampler->undo(transform);
}

