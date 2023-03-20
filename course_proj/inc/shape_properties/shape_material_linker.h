#ifndef _SHAPE_MATERIAL_LINKER_H_
#define _SHAPE_MATERIAL_LINKER_H_

#include <memory>

#include "dedicated_property.h"
#include "material.h"

class ShapeMaterialLinker : public DedicatedProperty
{
    public:
        static const size_t ATTRI = 3;
        static const Attribute &ATTRIBUTE(void);

    public:
        ShapeMaterialLinker(Shape *target, const std::shared_ptr<Material> &material);
        virtual ~ShapeMaterialLinker(void) override;
        virtual const Attribute &getAttribute(void) const override;

        const Material &getMaterial(void) const;
        void setMaterial(const std::shared_ptr<Material> &material);

    private:
        std::shared_ptr<Material> material;
};

#endif

