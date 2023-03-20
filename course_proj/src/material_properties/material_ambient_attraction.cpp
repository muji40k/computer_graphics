#include "material_ambient_attraction.h"

const Attribute &MaterialAmbientAttraction::ATTRIBUTE(void)
{
    static Attribute attr = MaterialProperty::ATTRIBUTE() \
                            | Attribute(MaterialAmbientAttraction::MAXATTR,
                                        {MaterialAmbientAttraction::ATTRI});
    return attr;
}

MaterialAmbientAttraction::MaterialAmbientAttraction(const Intensity<> &value)
    : value(std::make_shared<Intensity<>>(value)) {}

MaterialAmbientAttraction::~MaterialAmbientAttraction(void) {}

const Attribute &MaterialAmbientAttraction::getAttribute(void) const
{
    return MaterialAmbientAttraction::ATTRIBUTE();
}

const Intensity<> &MaterialAmbientAttraction::getValue(void)
{
    return *this->value;
}
