#include "image_array_texture_builder.h"

template <typename Type>
ImageArrayTextureBuilder<Type>::ImageArrayTextureBuilder(const char *const filename)
    : FileArrayTextureBuilder<Type>(filename) {}

template <typename Type>
ImageArrayTextureBuilder<Type>::~ImageArrayTextureBuilder(void) {}

