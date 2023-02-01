#include "null_object.h"

const Attribute &NullObject::ATTRIBUTE(void)
{
    static const Attribute attr = MetaObject::ATTRIBUTE() | \
                                  Attribute(NullObject::MAXATTR,
                                            {NullObject::ATTRI});
    return attr;
}

NullObject::~NullObject(void) {}

const Attribute &NullObject::getAttribute(void) const
{
    return NullObject::ATTRIBUTE();
}

Intersection NullObject::intersect(const Ray3<double> &) const
{
    return Intersection();
}

bool NullObject::intersectBounding(const Ray3<double> &) const
{
    return false;
}

double NullObject::area(void) const { return 0; }

void NullObject::apply(const Transform<double, 3> &) {}
void NullObject::undo(const Transform<double, 3> &) {}

