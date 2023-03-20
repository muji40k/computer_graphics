#include "environment_map.h"

const Attribute &EnvironmentMap::ATTRIBUTE(void)
{
    static Attribute attr = CommonProperty::ATTRIBUTE() \
                            | Attribute(EnvironmentMap::MAXATTR,
                                        {EnvironmentMap::ATTRI});
    return attr;
}

EnvironmentMap::EnvironmentMap(const std::shared_ptr<Texture<Intensity<>>> &texture,
                               const double &size)
    : texture(texture), size(size) {}

EnvironmentMap::~EnvironmentMap(void) {}

const Attribute &EnvironmentMap::getAttribute(void) const
{
    return EnvironmentMap::ATTRIBUTE();
}

void EnvironmentMap::setTexture(const std::shared_ptr<Texture<Intensity<>>> &texture)
{
    this->texture = texture;
}

void EnvironmentMap::setSize(const double &size)
{
    this->size = size;
}

