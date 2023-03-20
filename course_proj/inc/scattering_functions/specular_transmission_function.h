#ifndef _SPECULAR_TRANSMISSION_FUNCTION_H_
#define _SPECULAR_TRANSMISSION_FUNCTION_H_

#include "transmission_function.h"

class SpecularTransmissionFunction : public TransmissionFunction
{
    public:
        SpecularTransmissionFunction(const Intensity<> &value);
        virtual ~SpecularTransmissionFunction(void) override;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        std::shared_ptr<Intensity<>> value;
};

#endif

