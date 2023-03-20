#include "shape_material_linker.h"

ShapeMaterialLinker::ShapeMaterialLinker(Shape *target,
                                         const std::shared_ptr<Material> &material)
    : DedicatedProperty(target), material(material) {}

ShapeMaterialLinker::~ShapeMaterialLinker(void) {}

const Attribute &ShapeMaterialLinker::ATTRIBUTE(void)
{
    static const Attribute attr = DedicatedProperty::ATTRIBUTE() \
                                  | Attribute(ShapeMaterialLinker::MAXATTR,
                                              {ShapeMaterialLinker::ATTRI});
    return attr;
}

const Attribute &ShapeMaterialLinker::getAttribute(void) const
{
    return ShapeMaterialLinker::ATTRIBUTE();
}

const Material &ShapeMaterialLinker::getMaterial(void) const
{
    return *this->material;
}

void ShapeMaterialLinker::setMaterial(const std::shared_ptr<Material> &material)
{
    this->material = material;
}

