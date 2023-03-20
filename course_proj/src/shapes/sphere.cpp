#include "sphere.h"

#include <float.h>
#include <cmath>

#include "bounding_sphere.h"

#include "sphere_sampler.h"

#include "tools.h"

const Attribute &Sphere::ATTRIBUTE(void)
{
    static const Attribute attr = ParametricModel::ATTRIBUTE() \
                                  | Attribute(Sphere::MAXATTR,
                                              {Sphere::ATTRI});
    return attr;
}

Sphere::~Sphere(void) {}

Sphere::Sphere(double radius)
{
    if (radius < 0)
        throw CALL_EX(DegenerateSphereException);

    this->radius = radius;
    this->radiussqr = radius * radius;

    Point3<double> center;

    this->transform_local = std::make_shared<Transform<double, 3>>();

    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(center + Vector3<double>({radius, 0, 0}));
    this->bounding->expand(center + Vector3<double>({-radius, 0, 0}));

    this->sampler = std::make_shared<SphereSampler>(radius);
}

bool Sphere::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);
    tmp.undo(*this->transform_local);

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
    tmp.undo(*this->transform_local);

    Point3<double> center;
    Vector3<double> vtmp = center > tmp.getOrigin();

    tools::sqr_eq_res_t res = tools::solve_sqr(tmp.getDirection().lengthSqr(),
                                               2 * (vtmp & tmp.getDirection()),
                                               vtmp.lengthSqr() - this->radiussqr);

    double t = -1;

    for (int i = 0; res.n > i; i++)
        if (FLT_EPSILON < res.x[i] && (t < 0 || t > res.x[i]))
            t = res.x[i];

    if (t > 0)
    {
        Point3<double> point = tmp(t);
        Normal3<double> normal (center, point);
        normal.normalise();

        double u = 0.5 + atan2(-normal.x, -normal.z) / (2 * M_PI);
        double v = acos(-normal.y) / M_PI;

        out = Intersection(this, point, Point2<double>({u, v}), normal, t,
                           *this->transform_local + *this->transform_global);
    }

    return out;
}

void Sphere::apply(const Transform<double, 3> &transform)
{
    *this->transform_local += transform;
    this->sampler->apply(transform);
}

void Sphere::undo(const Transform<double, 3> &transform)
{
    *this->transform_local += transform.inversed();
    this->sampler->undo(transform);
}

