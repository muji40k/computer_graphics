#include "scattering_scale.h"

const Attribute &ScatteringScale::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringScale::MAXATTR,
                                        {ScatteringScale::ATTRI});
    return attr;
}

ScatteringScale::ScatteringScale(const Intensity<> scale)
    : scale(std::make_shared<Intensity<>>(scale)) {}

ScatteringScale::~ScatteringScale(void) {}

const Intensity<> &ScatteringScale::getScale(void)
{
    return *this->scale;
}

const Attribute &ScatteringScale::getAttribute(void) const
{
    return ScatteringScale::ATTRIBUTE();
}

