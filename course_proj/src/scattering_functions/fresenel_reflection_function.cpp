#include "fresenel_reflection_function.h"

FresnelReflectionFunction::FresnelReflectionFunction(const Intensity<> &scale,
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

FresnelReflectionFunction::~FresnelReflectionFunction(void) {}

