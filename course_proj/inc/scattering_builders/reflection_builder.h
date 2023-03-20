#ifndef _REFLECTION_BUILDER_H_
#define _REFLECTION_BUILDER_H_

#include "scattering_builder.h"

class ReflectionBuilder : public ScatteringBuilder
{
    public:
        static const size_t ATTRI = 3;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ReflectionBuilder(void) override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

