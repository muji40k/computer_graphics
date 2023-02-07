#include "intersection.h"

Intersection::Intersection(void) : valid(false) {};
Intersection::~Intersection(void) {};

Intersection::Intersection(const Shape *const shape,
                           const Point3<double> &point,
                           const Point2<double> &pointuv,
                           const Normal3<double> &normal,
                           double t,
                           const Transform<double, 3> &transform)
    : valid(true), t(t), point(point), pointuv(pointuv), normal(normal),
      transform(transform), shape(shape)
{
    if (!shape)
        throw CALL_EX(NullPointerPolygonException);
}

Intersection::operator bool(void) const
{
    return this->valid;
}

double Intersection::getT(void) const
{
    return this->t;
}

const Shape *Intersection::getShape(void) const
{
    return this->shape;
}

const Point3<double> &Intersection::getPoint(void) const
{
    return this->point;
}

const Normal3<double> &Intersection::getNormal(void) const
{
    return this->normal;
}

const Transform<double, 3> &Intersection::toGlobal(void) const
{
    return this->transform;
}

void Intersection::apply(const Transform<double, 3> &transform)
{
    this->transform += transform;
}

void Intersection::undo(const Transform<double, 3> &transform)
{
    this->transform += transform.inversed();
}

