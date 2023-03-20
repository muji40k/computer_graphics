#ifndef _TEXTURE_BUILDER_H_
#define _TEXTURE_BUILDER_H_

#include <memory>

#include "base_exception.h"

#include "texture.h"

template <typename Type>
class TextureBuilder
{
    public:
        virtual ~TextureBuilder(void) = 0;
        virtual std::shared_ptr<Texture<Type>> build(void) = 0;
};

class CommonTextureBuilderException: public BaseException
{
    public:
        CommonTextureBuilderException(void) = default;
        CommonTextureBuilderException(const char *filename, const size_t line,
                                    const char *function,
                                    const char *message = "General texture builder exception")
            : BaseException(filename, line, function, message) {};
        ~CommonTextureBuilderException(void) = default;
};

#include "texture_builder.hpp"

#endif

