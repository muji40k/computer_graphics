#include "scattering_refraction_index_out.h"

const Attribute &ScatteringRefractionIndexOut::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringRefractionIndexOut::MAXATTR,
                                        {ScatteringRefractionIndexOut::ATTRI});
    return attr;
}

ScatteringRefractionIndexOut::ScatteringRefractionIndexOut(const std::complex<double> &prop)
{
    this->ref_index = std::make_shared<std::complex<double>>(prop);
}

ScatteringRefractionIndexOut::~ScatteringRefractionIndexOut(void) {}

const Attribute &ScatteringRefractionIndexOut::getAttribute(void) const
{
    return ScatteringRefractionIndexOut::ATTRIBUTE();
}

const std::complex<double> &ScatteringRefractionIndexOut::getRefractionIndex(void)
{
    return *this->ref_index;
}

