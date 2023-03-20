#ifndef _FRESENEL_TRANSMISSION_FUNCTION_H_
#define _FRESENEL_TRANSMISSION_FUNCTION_H_

#include "transmission_function.h"

#include "intersection.h"
#include <complex>

class FresnelTransmissionFunction : public TransmissionFunction
{
    public:
        FresnelTransmissionFunction(const Intensity<> &intensity,
                                    const Intersection &inter,
                                    const std::complex<double> &n1,
                                    const std::complex<double> &n2);
        virtual ~FresnelTransmissionFunction(void) override;

        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const override;

    private:
        std::shared_ptr<Intensity<>> scale;
        std::shared_ptr<std::complex<double>> n1;
        std::shared_ptr<std::complex<double>> n2;
        std::shared_ptr<Normal3<double>> cached_normal;
};

#endif

