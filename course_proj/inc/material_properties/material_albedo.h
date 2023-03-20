#ifndef _MATERIAL_ALBEDO_H_
#define _MATERIAL_ALBEDO_H_

#include <memory>

#include "material_property.h"
#include "intensity.h"

class MaterialAlbedo : public MaterialProperty
{
    public:
        static const size_t ATTRI = 3;
        static const Attribute &ATTRIBUTE(void);

    public:
        MaterialAlbedo(const Intensity<> &albedo);
        virtual ~MaterialAlbedo(void) override;
        virtual const Attribute &getAttribute(void) const override;

        const Intensity<> &getValue(void);

    private:
        std::shared_ptr<Intensity<>> albedo;
};

#endif

