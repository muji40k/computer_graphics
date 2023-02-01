#include <float.h>
#include "disk.h"
#include "vector.h"

#include "bounding_sphere.h"

#include "disk_sampler.h"

const Attribute &Disk::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Disk::MAXATTR, {Disk::ATTRI});
    return attr;
}

Disk::~Disk(void) {}

Disk::Disk(const Point3<double> &center,
           const Vector3<double> &normal,
           double radius)
{
    if (0 > radius)
        throw CALL_EX(NegativeRadiusDiskException);

    this->center = std::make_shared<Point3<double>>(center);
    this->normal = std::make_shared<Vector3<double>>(normal);
    this->radius = radius;
    this->rsqr = radius * radius;

    this->bounding = std::make_shared<BoundingSphere>(center);
    this->bounding->expand(center + Vector3<double>({radius, 0, 0}));
    // this->bounding->expand(center + Vector3<double>({0, radius, 0}));
    this->bounding->expand(center + Vector3<double>({-radius, 0, 0}));
    // this->bounding->expand(center + Vector3<double>({0, -radius, 0}));

    this->sampler = std::make_shared<DiskSampler>(center, normal, radius);
}

bool Disk::intersectBounding(const Ray3<double> &ray) const
{
    Ray3 tmp (ray);
    tmp.undo(*this->transform_global);

    return this->bounding->intersect(tmp);
}

const Attribute &Disk::getAttribute(void) const
{
    return Disk::ATTRIBUTE();
}

Intersection Disk::intersect(const Ray3<double> &ray) const
{
    Intersection out = Intersection();

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    double t = ((tmp.getOrigin() > *(this->center)) & *(this->normal)) \
               / (tmp.getDirection() & *(this->normal));

    if (FLT_EPSILON > t)
        return out;

    Point3<double> point = tmp(t);

    if (this->radius > distance(point, *(this->center)))
        out = Intersection(this, point, Normal3<double>(*(this->normal)), t,
                           *this->transform_global);

    return out;
}

double Disk::area(void) const
{
    return M_PI * this->rsqr;
}

const ShapeSampler &Disk::getSampler(void) const
{
    return *this->sampler;
}

void Disk::apply(const Transform<double, 3> &transform)
{
    this->center->apply(transform);
    this->normal->apply(transform);
    this->bounding->apply(transform);
    this->sampler->apply(transform);
}

void Disk::undo(const Transform<double, 3> &transform)
{
    this->center->undo(transform);
    this->normal->undo(transform);
    this->bounding->undo(transform);
    this->sampler->undo(transform);
}

