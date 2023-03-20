#ifndef _TRACER_LIGHT_SAMPLES_H_
#define _TRACER_LIGHT_SAMPLES_H_

#include "tracer_property.h"

class TracerLightSamples : public TracerProperty
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        TracerLightSamples(const size_t depth);
        virtual ~TracerLightSamples(void) override;
        virtual const Attribute &getAttribute(void) const override;

        size_t getValue(void) const;

    private:
        size_t depth;
};

#endif

