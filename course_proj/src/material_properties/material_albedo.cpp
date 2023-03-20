#include "material_albedo.h"

const Attribute &MaterialAlbedo::ATTRIBUTE(void)
{
    static Attribute attr = MaterialProperty::ATTRIBUTE() \
                            | Attribute(MaterialAlbedo::MAXATTR,
                                        {MaterialAlbedo::ATTRI});
    return attr;
}

MaterialAlbedo::MaterialAlbedo(const Intensity<> &albedo)
    : albedo(std::make_shared<Intensity<>>(albedo)) {}

MaterialAlbedo::~MaterialAlbedo(void) {}

const Attribute &MaterialAlbedo::getAttribute(void) const
{
    return MaterialAlbedo::ATTRIBUTE();
}

const Intensity<> &MaterialAlbedo::getValue(void)
{
    return *this->albedo;
}

