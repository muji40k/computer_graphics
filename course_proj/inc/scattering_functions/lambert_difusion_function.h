#ifndef _LAMBERTION_DIFUSION_FUNCTION_H_
#define _LAMBERTION_DIFUSION_FUNCTION_H_

#include "difusion_function.h"

class LambertDifusionFunction : public DifusionFunction
{
    public:
        LambertDifusionFunction(const Intensity<> &value);
        virtual ~LambertDifusionFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        std::shared_ptr<Intensity<>> value;
};


#endif

