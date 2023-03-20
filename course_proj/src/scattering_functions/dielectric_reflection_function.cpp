#include "dielectric_reflection_function.h"

#include "tools.h"

DielectricReflectionFunction::DielectricReflectionFunction(const Intensity<> &intensity,
                                                         const Intersection &inter,
                                                         const std::complex<double> &n1,
                                                         const std::complex<double> &n2)
    : FresnelReflectionFunction(intensity, inter, n1, n2) {}

DielectricReflectionFunction::~DielectricReflectionFunction(void) {}

Intensity<> DielectricReflectionFunction::apply(const Vector3<double> &in,
                                                const Vector3<double> &) const
{
    return tools::fresnel_dielectric(in, *this->cached_normal, this->n1->real(),
                                     this->n2->real()) \
           * *this->scale;
}

