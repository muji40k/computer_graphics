#ifndef _SCATTERING_SCALE_H_
#define _SCATTERING_SCALE_H_

#include <memory>

#include "scattering_property.h"
#include "intensity.h"

class ScatteringScale : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringScale(const Intensity<> scale);
        virtual ~ScatteringScale(void) override;
        const Intensity<> &getScale(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<Intensity<>> scale;

};

#endif

