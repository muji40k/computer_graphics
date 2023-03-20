#include "tracer_property.h"

const Attribute &TracerProperty::ATTRIBUTE(void)
{
    static Attribute attr (TracerProperty::MAXATTR, {TracerProperty::ATTRI});
    return attr;
}

TracerProperty::~TracerProperty(void) {}

const Attribute &TracerProperty::getAttribute(void) const
{
    return TracerProperty::ATTRIBUTE();
}

