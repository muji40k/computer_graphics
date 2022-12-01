#include "object.h"

const Attribute &Object::ATTRIBUTE(void)
{
    static const Attribute attr = Shape::ATTRIBUTE() \
                                  | Attribute(Object::MAXATTR,
                                              {Object::ATTRI});
    return attr;
}

Object::~Object(void) {}

const Attribute &Object::getAttribute(void) const
{
    return Object::ATTRIBUTE();
}

