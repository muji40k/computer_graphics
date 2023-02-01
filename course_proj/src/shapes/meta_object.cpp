#include "meta_object.h"

const Attribute &MetaObject::ATTRIBUTE(void)
{
    static const Attribute attr = Shape::ATTRIBUTE() | \
                                  Attribute(MetaObject::MAXATTR,
                                            {MetaObject::ATTRI});
    return attr;
}

MetaObject::~MetaObject(void) {}

const Attribute &MetaObject::getAttribute(void) const
{
    return MetaObject::ATTRIBUTE();
}

const ShapeSampler &MetaObject::getSampler(void) const
{
    return this->sampler;
}

