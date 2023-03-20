#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "dedicated_property.h"
#include "intensity.h"

class Lighting : public DedicatedProperty
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        Lighting(Shape *target, const Intensity<> &emission = Intensity<>());
        virtual ~Lighting(void) override;

        const Intensity<> &getEmission(void) const;
        void setEmission(const Intensity<> &emission);

        virtual const Attribute &getAttribute(void) const override;

    private:
        Intensity<> emission;
};

#endif

