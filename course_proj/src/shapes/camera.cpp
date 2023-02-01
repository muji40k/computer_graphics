#include "camera.h"

const Attribute &Camera::ATTRIBUTE(void)
{
    static const Attribute attr = MetaObject::ATTRIBUTE() | \
                                  Attribute(Camera::MAXATTR,
                                            {Camera::ATTRI});
    return attr;
}

Camera::~Camera(void) {}

const Attribute &Camera::getAttribute(void) const
{
    return Camera::ATTRIBUTE();
}

Intersection Camera::intersect(const Ray3<double> &) const
{
    return Intersection();
}

bool Camera::intersectBounding(const Ray3<double> &) const
{
    return false;
}

double Camera::area(void) const { return 0; }

void Camera::apply(const Transform<double, 3> &) {}
void Camera::undo(const Transform<double, 3> &) {}

