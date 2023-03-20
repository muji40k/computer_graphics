#include "scattering_albedo.h"

const Attribute &ScatteringAlbedo::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringAlbedo::MAXATTR,
                                        {ScatteringAlbedo::ATTRI});
    return attr;
}

ScatteringAlbedo::ScatteringAlbedo(const Intensity<> albedo)
    : albedo(std::make_shared<Intensity<>>(albedo)) {}

ScatteringAlbedo::~ScatteringAlbedo(void) {}

const Intensity<> &ScatteringAlbedo::getAlbedo(void)
{
    return *this->albedo;
}

const Attribute &ScatteringAlbedo::getAttribute(void) const
{
    return ScatteringAlbedo::ATTRIBUTE();
}

