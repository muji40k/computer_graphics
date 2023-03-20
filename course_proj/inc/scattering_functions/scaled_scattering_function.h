#ifndef _SCALED_SCATTERING_FUNCTION_H_
#define _SCALED_SCATTERING_FUNCTION_H_

#include <memory>

#include "scattering_function.h"

class ScaledScatteringFunction : public ScatteringFunction
{
    public:
        ScaledScatteringFunction(const std::shared_ptr<const ScatteringFunction> &fucntion,
                                 const Intensity<> &scale);
        virtual ~ScaledScatteringFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        Intensity<> scale;
        std::shared_ptr<const ScatteringFunction> function;
};

#endif

