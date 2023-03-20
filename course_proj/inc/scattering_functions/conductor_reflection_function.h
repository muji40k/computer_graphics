#ifndef _CONDUCTOR_REFLECTION_FUNCTION_H_
#define _CONDUCTOR_REFLECTION_FUNCTION_H_

#include "fresenel_reflection_function.h"

class ConductorReflectionFunction : public FresnelReflectionFunction
{
    public:
        ConductorReflectionFunction(const Intensity<> &intensity,
                                    const Intersection &inter,
                                    const std::complex<double> &n1,
                                    const std::complex<double> &n2);
        virtual ~ConductorReflectionFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;
};

#endif

