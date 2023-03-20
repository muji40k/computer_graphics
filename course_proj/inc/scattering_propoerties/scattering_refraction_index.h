#ifndef _SCATTERING_REFRACTION_INDEX_H_
#define _SCATTERING_REFRACTION_INDEX_H_

#include "scattering_property.h"

#include <complex>

class ScatteringRefractionIndex : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 3;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringRefractionIndex(const std::complex<double> &prop);
        virtual ~ScatteringRefractionIndex(void) override;
        const std::complex<double> &getRefractionIndex(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<std::complex<double>> ref_index;
};

#endif

