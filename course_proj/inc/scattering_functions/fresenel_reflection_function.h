#ifndef _FRESENEL_REFLECTION_FUNCTION_H_
#define _FRESENEL_REFLECTION_FUNCTION_H_

#include <memory>

#include "reflection_function.h"

#include "intersection.h"
#include <complex>

class FresnelReflectionFunction : public ReflectionFunction
{
    public:
        FresnelReflectionFunction(const Intensity<> &scale,
                                  const Intersection &inter,
                                  const std::complex<double> &n1,
                                  const std::complex<double> &n2);
        virtual ~FresnelReflectionFunction(void) override;

    protected:
        std::shared_ptr<Intensity<>> scale;
        std::shared_ptr<std::complex<double>> n1;
        std::shared_ptr<std::complex<double>> n2;
        std::shared_ptr<Normal3<double>> cached_normal;
};

#endif

