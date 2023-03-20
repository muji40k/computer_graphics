#include "scattering_refraction_index_in.h"

const Attribute &ScatteringRefractionIndexIn::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringRefractionIndexIn::MAXATTR,
                                        {ScatteringRefractionIndexIn::ATTRI});
    return attr;
}

ScatteringRefractionIndexIn::ScatteringRefractionIndexIn(const std::complex<double> &prop)
{
    this->ref_index = std::make_shared<std::complex<double>>(prop);
}

ScatteringRefractionIndexIn::~ScatteringRefractionIndexIn(void) {}

const Attribute &ScatteringRefractionIndexIn::getAttribute(void) const
{
    return ScatteringRefractionIndexIn::ATTRIBUTE();
}

const std::complex<double> &ScatteringRefractionIndexIn::getRefractionIndex(void)
{
    return *this->ref_index;
}

