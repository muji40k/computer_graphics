#include <float.h>
#include "disk.h"
#include "vector.h"

const Attribute &Disk::ATTRIBUTE(void)
{
    static const Attribute attr = ObjectPrimitive::ATTRIBUTE() \
                                  | Attribute(Disk::MAXATTR, {Disk::ATTRI});
    return attr;
}

Disk::~Disk(void) {}

Disk::Disk(const Point3<double> &center,
     const Normal3<double> &normal,
     double radius)
{
    if (0 > radius)
        throw CALL_EX(NegativeRadiusDiskException);

    this->center = std::make_shared<Point3<double>>(center);
    this->normal = std::make_shared<Normal3<double>>(normal);
    this->radius = radius;
}

const Attribute &Disk::getAttribute(void) const
{
    return Disk::ATTRIBUTE();
}

Intersection Disk::intersect(const Ray3<double> &ray) const
{
    Intersection out = this->ObjectPrimitive::intersect(ray);

    Ray3<double> tmp (ray);
    tmp.undo(*this->transform_global);
    double t = ((tmp.getOrigin() > *(this->center)) & *(this->normal)) \
               / (tmp.getDirection() & *(this->normal));

    if (out && (FLT_EPSILON > t || out.getT() < t))
        return out;

    Point3<double> point = tmp(t);

    if (this->radius > distance(point, *(this->center)))
        out = Intersection(this, point, *(this->normal), t,
                           *this->transform_global);

    return out;
}

void Disk::apply(const Transform<double, 3> &transform)
{
    this->ObjectPrimitive::apply(transform);
    this->center->apply(transform);
    this->normal->apply(transform);
}

void Disk::undo(const Transform<double, 3> &transform)
{
    this->ObjectPrimitive::undo(transform);
    this->center->undo(transform);
    this->normal->undo(transform);
}

