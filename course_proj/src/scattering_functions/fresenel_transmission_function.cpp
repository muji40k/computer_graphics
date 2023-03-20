#include "fresenel_transmission_function.h"

#include "tools.h"

FresnelTransmissionFunction::FresnelTransmissionFunction(const Intensity<> &scale,
                                                         const Intersection &inter,
                                                         const std::complex<double> &n1,
                                                         const std::complex<double> &n2)
{
    this->scale = std::make_shared<Intensity<>>(scale);
    this->n1 = std::make_shared<std::complex<double>>(n1);
    this->n2 = std::make_shared<std::complex<double>>(n2);
    this->cached_normal = std::make_shared<Normal3<double>>(inter.getNormal());
    this->cached_normal->apply(inter.toGlobal());
}

FresnelTransmissionFunction::~FresnelTransmissionFunction(void) {}

Intensity<> FresnelTransmissionFunction::apply(const Vector3<double> &in,
                                               const Vector3<double> &) const
{
    return (1 - tools::fresnel_dielectric(in, *this->cached_normal,
                                          this->n1->real(), this->n2->real())) \
           * *this->scale;
}

