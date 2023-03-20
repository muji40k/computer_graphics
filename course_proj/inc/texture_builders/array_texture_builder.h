#ifndef _ARRAY_TEXTURE_BUILDER_H_
#define _ARRAY_TEXTURE_BUILDER_H_

#include "texture_builder.h"

template <typename Type>
class ArrayTextureBuilder : public TextureBuilder<Type>
{
    public:
        virtual ~ArrayTextureBuilder(void) = 0;
};

class CommonArrayTextureBuilderException: public CommonTextureBuilderException
{
    public:
        CommonArrayTextureBuilderException(void) = default;
        CommonArrayTextureBuilderException(const char *filename, const size_t line,
                                           const char *function,
                                           const char *message = "General array texture builder exception")
            : CommonTextureBuilderException(filename, line, function, message) {};
        ~CommonArrayTextureBuilderException(void) = default;
};

#include "array_texture_builder.hpp"

#endif

