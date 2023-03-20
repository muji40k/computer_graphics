#include "scattering_property.h"

const Attribute &ScatteringProperty::ATTRIBUTE(void)
{
    static Attribute attr (ScatteringProperty::MAXATTR,
                           {ScatteringProperty::ATTRI});
    return attr;
}

ScatteringProperty::~ScatteringProperty(void) {}

const Attribute &ScatteringProperty::getAttribute(void) const
{
    return ScatteringProperty::ATTRIBUTE();
}

