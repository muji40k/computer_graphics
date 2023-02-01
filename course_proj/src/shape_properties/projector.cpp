#include "projector.h"

Projector::Projector(Shape *target) : ShapeProperty(target) {}

Projector::~Projector(void) {}

const Attribute &Projector::ATTRIBUTE(void)
{
    static const Attribute attr = ShapeProperty::ATTRIBUTE() \
                                  | Attribute(Projector::MAXATTR,
                                              {Projector::ATTRI});
    return attr;
}

const Attribute &Projector::getAttribute(void) const
{
    return Projector::ATTRIBUTE();
}

