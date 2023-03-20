#include "specular_reflection_function.h"

SpecularReflectionFunction::SpecularReflectionFunction(const Intensity<> &value)
{
    this->value = std::make_shared<Intensity<>>(value);
}

SpecularReflectionFunction::~SpecularReflectionFunction(void) {}

Intensity<> SpecularReflectionFunction::apply(const Vector3<double> &,
                                              const Vector3<double> &) const
{
    return *this->value;
}

