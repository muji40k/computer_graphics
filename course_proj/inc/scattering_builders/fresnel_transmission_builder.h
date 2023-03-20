#ifndef _FRESNEL_TRANSMISSION_BUILDER_H_
#define _FRESNEL_TRANSMISSION_BUILDER_H_

#include "transmission_builder.h"

class FresnelTransmissionBuilder : public TransmissionBuilder
{
    public:
        static const size_t ATTRI = 31;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~FresnelTransmissionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

