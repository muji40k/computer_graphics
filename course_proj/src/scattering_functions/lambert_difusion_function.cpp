#include "lambert_difusion_function.h"

LambertDifusionFunction::LambertDifusionFunction(const Intensity<> &value)
{
    this->value = std::make_shared<Intensity<>>(value);
}

LambertDifusionFunction::~LambertDifusionFunction(void) {}

Intensity<> LambertDifusionFunction::apply(const Vector3<double> &,
                                           const Vector3<double> &) const
{
    return *this->value;
}

