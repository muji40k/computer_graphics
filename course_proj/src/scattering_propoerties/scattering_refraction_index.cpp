#include "scattering_refraction_index.h"

const Attribute &ScatteringRefractionIndex::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringRefractionIndex::MAXATTR,
                                        {ScatteringRefractionIndex::ATTRI});
    return attr;
}

ScatteringRefractionIndex::ScatteringRefractionIndex(const std::complex<double> &prop)
    : ref_index(std::make_shared<std::complex<double>>(prop)) {}

ScatteringRefractionIndex::~ScatteringRefractionIndex(void) {}

const std::complex<double> &ScatteringRefractionIndex::getRefractionIndex(void)
{
    return *this->ref_index;
}

const Attribute &ScatteringRefractionIndex::getAttribute(void) const
{
    return ScatteringRefractionIndex::ATTRIBUTE();
}

