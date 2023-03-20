#ifndef _PHONG_SPECULAR_BUILDER_H_
#define _PHONG_SPECULAR_BUILDER_H_

#include "difusion_builder.h"

class PhongSpecularBuilder : public DifusionBuilder
{
    public:
        static const size_t ATTRI = 11;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~PhongSpecularBuilder(void) override;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const override;
        virtual const Attribute &getAttribute(void) const override;
};

#endif

