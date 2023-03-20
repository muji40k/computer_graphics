#ifndef _MATERIAL_SCATTERING_H_
#define _MATERIAL_SCATTERING_H_

#include <memory>
#include <list>

#include "material_property.h"
#include "scattering_builder.h"

class MaterialScattering : public MaterialProperty
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        using BuilderInfo = struct
        {
            std::shared_ptr<const ScatteringBuilder> builder;
            std::shared_ptr<const ScatteringInfo> info;
        };

        MaterialScattering(const std::list<BuilderInfo> &builders);
        virtual ~MaterialScattering(void) override;
        virtual const Attribute &getAttribute(void) const override;

        const std::list<BuilderInfo> &getBuilders(void);

    private:
        std::list<BuilderInfo> builders;
};


#endif

