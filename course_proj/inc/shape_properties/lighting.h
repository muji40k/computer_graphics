#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "shape_property.h"
#include "intensity.h"

class Lighting : public ShapeProperty
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        Lighting(Shape *target, const Intensity<> emission = Intensity<>());
        virtual ~Lighting(void);

        const Intensity<> &getEmission(void) const;
        void setEmission(const Intensity<> emission);

        virtual const Attribute &getAttribute(void) const override;

    private:
        Intensity<> emission;
};

#endif

