#ifndef _IMAGE_ARRAY_TEXTURE_BUILDER_H_
#define _IMAGE_ARRAY_TEXTURE_BUILDER_H_

#include "file_array_texture_builder.h"

template <typename Type>
class ImageArrayTextureBuilder : public FileArrayTextureBuilder<Type>
{
    public:
        ImageArrayTextureBuilder(const char *const filename);
        virtual ~ImageArrayTextureBuilder(void) override;
        virtual std::shared_ptr<Texture<Type>> build(void) override;
};

class CommonImageArrayTextureBuilderException: public CommonFileArrayTextureBuilderException
{
    public:
        CommonImageArrayTextureBuilderException(void) = default;
        CommonImageArrayTextureBuilderException(const char *filename, const size_t line,
                                                const char *function,
                                                const char *message = "General image array texture builder exception")
            : CommonFileArrayTextureBuilderException(filename, line, function, message) {};
        ~CommonImageArrayTextureBuilderException(void) = default;
};

class AllocationImageArrayTextureBuilderException: public CommonImageArrayTextureBuilderException
{
    public:
        AllocationImageArrayTextureBuilderException(void) = default;
        AllocationImageArrayTextureBuilderException(const char *filename, const size_t line,
                                                const char *function,
                                                const char *message = "Allocation error")
            : CommonImageArrayTextureBuilderException(filename, line, function, message) {};
        ~AllocationImageArrayTextureBuilderException(void) = default;
};

#include "image_array_texture_builder.hpp"

#endif

