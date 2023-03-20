#include "light_array_texture_builder.h"

template <typename Type>
LightArrayTextureBuilder<Type>::LightArrayTextureBuilder(const char *const filename)
    : FileArrayTextureBuilder<Type>(filename) {}

template <typename Type>
LightArrayTextureBuilder<Type>::~LightArrayTextureBuilder(void) {}

