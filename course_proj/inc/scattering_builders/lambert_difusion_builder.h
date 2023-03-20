#ifndef _LAMBERT_DIFUSION_BUILDER_H_
#define _LAMBERT_DIFUSION_BUILDER_H_

#include "difusion_builder.h"

class LambertDifusionBuilder : public DifusionBuilder
{
    public:
        static const size_t ATTRI = 10;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~LambertDifusionBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

