#ifndef _CONDUCTOR_REFLECTION_BUILDER_H_
#define _CONDUCTOR_REFLECTION_BUILDER_H_

#include "fresnel_reflection_builder.h"

class ConductorReflectionBuilder : public FresnelReflectionBuilder
{
    public:
        static const size_t ATTRI = 23;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ConductorReflectionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

