#ifndef _FRESNEL_REFLECTION_BUILDER_H_
#define _FRESNEL_REFLECTION_BUILDER_H_

#include "reflection_builder.h"

class FresnelReflectionBuilder : public ReflectionBuilder
{
    public:
        static const size_t ATTRI = 21;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~FresnelReflectionBuilder(void) override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

