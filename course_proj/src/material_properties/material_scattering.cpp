#include "material_scattering.h"

const Attribute &MaterialScattering::ATTRIBUTE(void)
{
    static Attribute attr = MaterialProperty::ATTRIBUTE() \
                            | Attribute(MaterialScattering::MAXATTR,
                                        {MaterialScattering::ATTRI});
    return attr;
}

MaterialScattering::MaterialScattering(const std::list<BuilderInfo> &builders)
    : builders(builders) {}

MaterialScattering::~MaterialScattering(void) {}

const Attribute &MaterialScattering::getAttribute(void) const
{
    return MaterialScattering::ATTRIBUTE();
}

const std::list<MaterialScattering::BuilderInfo> &MaterialScattering::getBuilders(void)
{
    return this->builders;
}

