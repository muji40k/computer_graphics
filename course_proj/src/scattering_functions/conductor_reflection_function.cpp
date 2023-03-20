#include "conductor_reflection_function.h"

#include "tools.h"

ConductorReflectionFunction::ConductorReflectionFunction(const Intensity<> &intensity,
                                                         const Intersection &inter,
                                                         const std::complex<double> &n1,
                                                         const std::complex<double> &n2)
    : FresnelReflectionFunction(intensity, inter, n1, n2) {}

ConductorReflectionFunction::~ConductorReflectionFunction(void) {}

Intensity<> ConductorReflectionFunction::apply(const Vector3<double> &in,
                                               const Vector3<double> &) const
{
    return tools::fresnel_conductor(in, *this->cached_normal, this->n1->real(),
                                    *this->n2) \
           * *this->scale;
}

