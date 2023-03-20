#include "file_array_texture_builder.h"
#include <iostream>

template <typename Type>
FileArrayTextureBuilder<Type>::FileArrayTextureBuilder(const char *const filename)
    : filename(filename) {}

template <typename Type>
FileArrayTextureBuilder<Type>::~FileArrayTextureBuilder(void) {}

