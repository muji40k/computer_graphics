#ifndef _SCALED_SCATTERING_BUILDER_H_
#define _SCALED_SCATTERING_BUILDER_H_

#include "scattering_builder.h"

class ScaledScatteringBuilder : public ScatteringBuilder
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ScaledScatteringBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

