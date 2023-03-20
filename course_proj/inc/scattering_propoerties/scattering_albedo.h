#ifndef _SCATTERING_ALBEDO_H_
#define _SCATTERING_ALBEDO_H_

#include "scattering_property.h"

#include "intensity.h"

class ScatteringAlbedo : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 4;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringAlbedo(const Intensity<> albedo);
        virtual ~ScatteringAlbedo(void) override;
        const Intensity<> &getAlbedo(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<Intensity<>> albedo;

};

#endif

