#include "scaled_scattering_function.h"

ScaledScatteringFunction::ScaledScatteringFunction(const std::shared_ptr<const ScatteringFunction> &fucntion,
                                                   const Intensity<> &scale)
    : scale(scale), function(fucntion) {}

ScaledScatteringFunction::~ScaledScatteringFunction(void) {}

Intensity<> ScaledScatteringFunction::apply(const Vector3<double> &in,
                                            const Vector3<double> &out) const
{
    return this->scale * this->function->apply(in, out);
}

