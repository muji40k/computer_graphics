#ifndef _SPECULAR_TRANSMISSION_BUILDER_H_
#define _SPECULAR_TRANSMISSION_BUILDER_H_

#include "transmission_builder.h"

class SpecularTransmissionBuilder : public TransmissionBuilder
{
    public:
        static const size_t ATTRI = 30;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~SpecularTransmissionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

