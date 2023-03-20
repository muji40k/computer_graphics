#ifndef _DIFUSION_BUILDER_H_
#define _DIFUSION_BUILDER_H_

#include "scattering_builder.h"

class DifusionBuilder : public ScatteringBuilder
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~DifusionBuilder(void) override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

