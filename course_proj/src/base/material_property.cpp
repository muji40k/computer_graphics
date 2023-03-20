#include "material_property.h"

const Attribute &MaterialProperty::ATTRIBUTE(void)
{
    static Attribute attr (MaterialProperty::MAXATTR, {MaterialProperty::ATTRI});
    return attr;
}

MaterialProperty::~MaterialProperty(void) {}

const Attribute &MaterialProperty::getAttribute(void) const
{
    return MaterialProperty::ATTRIBUTE();
}

