#include "sphere.h"

#include <float.h>
#include <cmath>

#include "bounding_sphere.h"

#include "sphere_sampler.h"

const Attribute &Sphere::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Sphere::MAXATTR,
                                              {Sphere::ATTRI});
    return attr;
}

Sphere::~Sphere(void) {}

Sphere::Sphere(const Point3<double> &center, double radius)
{
    if (radius < 0)
        throw CALL_EX(DegenerateSphereException);

    this->center = std::make_shared<Point3<double>>(center);
    this->radius = radius;
    this->radiussqr = radius * radius;

    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(center + Vector3<double>({radius, 0, 0}));
    this->bounding->expand(center + Vector3<double>({-radius, 0, 0}));

    this->sampler = std::make_shared<SphereSampler>(center, radius);
}

bool Sphere::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    return this->bounding->intersect(tmp);
}

double Sphere::area(void) const
{
    return 4 * M_PI * this->radiussqr;
}

const ShapeSampler &Sphere::getSampler(void) const
{
    return *this->sampler;
}

const Attribute &Sphere::getAttribute(void) const
{
    return Sphere::ATTRIBUTE();
}

Intersection Sphere::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);

    Vector3<double> vtmp = *(this->center) > tmp.getOrigin();
    double origin_center = vtmp.length();
    double origin_center_ray = vtmp & tmp.getDirection();
    double ray_length = tmp.getDirection().length();
    double ray_length_sqr = ray_length * ray_length;
    double t;

    double discriminant = origin_center_ray * origin_center_ray \
                          - ray_length_sqr \
                            * (origin_center * origin_center - this->radiussqr);

    if (discriminant < -FLT_EPSILON)
        return out;

    if (FLT_EPSILON > fabs(discriminant))
    {
        t = - origin_center_ray / ray_length_sqr;

        if (FLT_EPSILON > t)
            t = -1;
    }
    else
    {
        double d = sqrt(discriminant);
        double t1, t2;
        t1 = ((-origin_center_ray) - d) / ray_length_sqr;
        t2 =  ((-origin_center_ray) + d) / ray_length_sqr;

        if (t1 > t2)
        {
            t = t1;
            t1 = t2;
            t2 = t;
        }

        if (FLT_EPSILON < t1)
            t = t1;
        else if (FLT_EPSILON < t2)
            t = t2;
        else
            t = -1;
    }


    if (t > 0)
    {
        Point3<double> point = tmp(t);
        Normal3<double> normal (*this->center, point);
        normal.normalise();

        out = Intersection(this, point, normal, t,
                           *this->transform_global);
    }

    return out;
}

void Sphere::apply(const Transform<double, 3> &transform)
{
    this->center->apply(transform);
    this->bounding->apply(transform);
    this->sampler->apply(transform);
}

void Sphere::undo(const Transform<double, 3> &transform)
{
    this->center->undo(transform);
    this->bounding->undo(transform);
    this->sampler->undo(transform);
}

