#ifndef _TRANSMISSION_BUILDER_H_
#define _TRANSMISSION_BUILDER_H_

#include "scattering_builder.h"

class TransmissionBuilder : public ScatteringBuilder
{
    public:
        static const size_t ATTRI = 4;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~TransmissionBuilder(void) override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

