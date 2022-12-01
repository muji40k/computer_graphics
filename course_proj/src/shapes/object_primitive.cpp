#include "object_primitive.h"

const Attribute &ObjectPrimitive::ATTRIBUTE(void)
{
    static const Attribute attr = Object::ATTRIBUTE() \
                                  | Attribute(ObjectPrimitive::MAXATTR,
                                              {ObjectPrimitive::ATTRI});
    return attr;
}

ObjectPrimitive::~ObjectPrimitive(void) {}

const Attribute &ObjectPrimitive::getAttribute(void) const
{
    return ObjectPrimitive::ATTRIBUTE();
}
