#ifndef _SPECULAR_REFLECTION_FUNCTION_H_
#define _SPECULAR_REFLECTION_FUNCTION_H_

#include "reflection_function.h"

class SpecularReflectionFunction : public ReflectionFunction
{
    public:
        SpecularReflectionFunction(const Intensity<> &value);
        virtual ~SpecularReflectionFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        std::shared_ptr<Intensity<>> value;
};

#endif

