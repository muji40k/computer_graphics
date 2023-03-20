#ifndef _LIGHT_ARRAY_TEXTURE_BUILDER_H_
#define _LIGHT_ARRAY_TEXTURE_BUILDER_H_

#include "file_array_texture_builder.h"

template <typename Type>
class LightArrayTextureBuilder : public FileArrayTextureBuilder<Type>
{
    public:
        LightArrayTextureBuilder(const char *const filename);
        virtual ~LightArrayTextureBuilder(void) override;
        virtual std::shared_ptr<Texture<Type>> build(void) override;
};

DEF_EX(CommonLightArrayTextureBuilderException, CommonFileArrayTextureBuilderException,
       "General image array texture builder exception");
DEF_EX(AllocationLightArrayTextureBuilderException, CommonLightArrayTextureBuilderException,
       "Allocation error");

#include "light_array_texture_builder.hpp"

#endif

