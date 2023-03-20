#ifndef _SCATTERING_REFRACTION_INDEX_IN_H_
#define _SCATTERING_REFRACTION_INDEX_IN_H_

#include <complex>

#include "scattering_property.h"

class ScatteringRefractionIndexIn : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 7;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringRefractionIndexIn(const std::complex<double> &prop);
        virtual ~ScatteringRefractionIndexIn(void) override;
        virtual const Attribute &getAttribute(void) const override;
        const std::complex<double> &getRefractionIndex(void);

    private:
        std::shared_ptr<std::complex<double>> ref_index;
};

#endif

