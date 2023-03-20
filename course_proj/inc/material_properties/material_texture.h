#ifndef _MATERIAL_TEXTURE_H_
#define _MATERIAL_TEXTURE_H_

#include <memory>

#include "material_property.h"
#include "texture.h"
#include "texture_mapper.h"
#include "intensity.h"

class MaterialTexture : public MaterialProperty
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        MaterialTexture(const std::shared_ptr<Texture<Intensity<>>> &texture,
                        const std::shared_ptr<TextureMapper> &mapper);
        virtual ~MaterialTexture(void) override;
        virtual const Attribute &getAttribute(void) const override;

        std::shared_ptr<Texture<Intensity<>>> getTexture(void);
        std::shared_ptr<TextureMapper> getMapper(void);

    private:
        std::shared_ptr<Texture<Intensity<>>> texture;
        std::shared_ptr<TextureMapper> mapper;
};

#endif

