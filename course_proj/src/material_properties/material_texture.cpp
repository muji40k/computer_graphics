#include "material_texture.h"

const Attribute &MaterialTexture::ATTRIBUTE(void)
{
    static Attribute attr = MaterialProperty::ATTRIBUTE() \
                            | Attribute(MaterialTexture::MAXATTR,
                                        {MaterialTexture::ATTRI});
    return attr;
}

MaterialTexture::MaterialTexture(const std::shared_ptr<Texture<Intensity<>>> &texture,
                                 const std::shared_ptr<TextureMapper> &mapper)
    : texture(texture), mapper(mapper) {}

MaterialTexture::~MaterialTexture(void) {}

const Attribute &MaterialTexture::getAttribute(void) const
{
    return MaterialTexture::ATTRIBUTE();
}

std::shared_ptr<Texture<Intensity<>>> MaterialTexture::getTexture(void)
{
    return this->texture;
}

std::shared_ptr<TextureMapper> MaterialTexture::getMapper(void)
{
    return this->mapper;
}

