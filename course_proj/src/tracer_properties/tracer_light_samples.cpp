#include "tracer_light_samples.h"

const Attribute &TracerLightSamples::ATTRIBUTE(void)
{
    static Attribute attr = TracerProperty::ATTRIBUTE() \
                            | Attribute(TracerLightSamples::MAXATTR,
                                        {TracerLightSamples::ATTRI});
    return attr;
}

TracerLightSamples::TracerLightSamples(const size_t depth)
{
    this->depth = depth;
}

TracerLightSamples::~TracerLightSamples(void) {}

const Attribute &TracerLightSamples::getAttribute(void) const
{
    return TracerLightSamples::ATTRIBUTE();
}

size_t TracerLightSamples::getValue(void) const
{
    return this->depth;
}

