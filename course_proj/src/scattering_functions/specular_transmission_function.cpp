#include "specular_transmission_function.h"

SpecularTransmissionFunction::SpecularTransmissionFunction(const Intensity<> &value)
{
    this->value = std::make_shared<Intensity<>>(value);
}

SpecularTransmissionFunction::~SpecularTransmissionFunction(void) {}

Intensity<> SpecularTransmissionFunction::apply(const Vector3<double> &,
                                                const Vector3<double> &) const
{
    return *this->value;
}

