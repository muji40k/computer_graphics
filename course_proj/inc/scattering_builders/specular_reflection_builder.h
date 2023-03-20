#ifndef _SPECULAR_REFLECTION_BUILDER_H_
#define _SPECULAR_REFLECTION_BUILDER_H_

#include "reflection_builder.h"

class SpecularReflectionBuilder : public ReflectionBuilder
{
    public:
        static const size_t ATTRI = 20;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~SpecularReflectionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

