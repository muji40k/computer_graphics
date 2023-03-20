#ifndef _FILE_ARRAY_TEXTURE_BUILDER_H_
#define _FILE_ARRAY_TEXTURE_BUILDER_H_

#include <fstream>

#include "array_texture_builder.h"

template <typename Type>
class FileArrayTextureBuilder : public TextureBuilder<Type>
{
    public:
        FileArrayTextureBuilder(const char *const filename);
        virtual ~FileArrayTextureBuilder(void) = 0;

    protected:
        const char *const filename;
};

class CommonFileArrayTextureBuilderException: public CommonArrayTextureBuilderException
{
    public:
        CommonFileArrayTextureBuilderException(void) = default;
        CommonFileArrayTextureBuilderException(const char *filename, const size_t line,
                                               const char *function,
                                               const char *message = "General texture builder exception")
            : CommonArrayTextureBuilderException(filename, line, function, message) {};
        ~CommonFileArrayTextureBuilderException(void) = default;
};

class NoFileArrayTextureBuilderException: public CommonFileArrayTextureBuilderException
{
    public:
        NoFileArrayTextureBuilderException(void) = default;
        NoFileArrayTextureBuilderException(const char *filename, const size_t line,
                                           const char *function,
                                           const char *message = "File given to file texture builder doesn't exists")
            : CommonFileArrayTextureBuilderException(filename, line, function, message) {};
        ~NoFileArrayTextureBuilderException(void) = default;
};

#include "file_array_texture_builder.hpp"

#endif

