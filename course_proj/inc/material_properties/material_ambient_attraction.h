#ifndef _MATERIAL_AMBIENT_ATTRACTION_H_
#define _MATERIAL_AMBIENT_ATTRACTION_H_

#include <memory>

#include "material_property.h"
#include "intensity.h"

class MaterialAmbientAttraction : public MaterialProperty
{
    public:
        static const size_t ATTRI = 5;
        static const Attribute &ATTRIBUTE(void);

    public:
        MaterialAmbientAttraction(const Intensity<> &value);
        virtual ~MaterialAmbientAttraction(void) override;
        virtual const Attribute &getAttribute(void) const override;

        const Intensity<> &getValue(void);

    private:
        std::shared_ptr<Intensity<>> value;
};

#endif

