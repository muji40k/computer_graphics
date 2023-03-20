#ifndef _AMBIENT_LIGHTING_H_
#define _AMBIENT_LIGHTING_H_

#include "common_property.h"

#include "intensity.h"

class AmbientLighting : public CommonProperty
{
    public:
        static const size_t ATTRI = 5;
        static const Attribute &ATTRIBUTE(void);

    public:
        AmbientLighting(const Intensity<> emission = Intensity<>());
        virtual ~AmbientLighting(void) override;

        const Intensity<> &getEmission(void) const;
        void setEmission(const Intensity<> emission);

        virtual const Attribute &getAttribute(void) const override;

    private:
        Intensity<> emission;
};

#endif

