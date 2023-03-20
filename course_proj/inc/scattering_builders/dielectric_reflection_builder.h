#ifndef _DIELECTRIC_REFLECTION_BUILDER_H_
#define _DIELECTRIC_REFLECTION_BUILDER_H_

#include "fresnel_reflection_builder.h"

class DielectricReflectionBuilder : public FresnelReflectionBuilder
{
    public:
        static const size_t ATTRI = 22;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~DielectricReflectionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

