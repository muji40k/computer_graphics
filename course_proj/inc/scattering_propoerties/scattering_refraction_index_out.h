#ifndef _SCATTERING_REFRACTION_INDEX_OUT_H_
#define _SCATTERING_REFRACTION_INDEX_OUT_H_

#include <complex>

#include "scattering_property.h"

class ScatteringRefractionIndexOut : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 8;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringRefractionIndexOut(const std::complex<double> &prop);
        virtual ~ScatteringRefractionIndexOut(void) override;
        virtual const Attribute &getAttribute(void) const override;
        const std::complex<double> &getRefractionIndex(void);

    private:
        std::shared_ptr<std::complex<double>> ref_index;
};

#endif

