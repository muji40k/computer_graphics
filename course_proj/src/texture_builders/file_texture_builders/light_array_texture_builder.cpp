#include "light_array_texture_builder.h"

#include "matrix.h"

#include "intensity.h"
#include "array_texture.h"

#include "stb_image.h"

template <>
std::shared_ptr<Texture<Intensity<>>> LightArrayTextureBuilder<Intensity<>>::build(void)
{
    int width, height, bpp;

    if (EXIT_SUCCESS == stbi_info(this->filename, &width, &height, &bpp))
        throw CALL_EX(NoFileArrayTextureBuilderException);

    float *image = stbi_loadf(this->filename, &width, &height, &bpp, 0);

    if (NULL == image)
        throw CALL_EX(AllocationLightArrayTextureBuilderException);

    int lim = (bpp > 3) ? 3 : bpp;
    int linewidth = bpp * width;

    Matrix<Intensity<>> mat ((size_t)height, (size_t)width);

    for (int i = 0; height > i; i++)
        for (int j = 0; width > j; j++)
            for (int k = 0; lim > k; k++)
                mat[i][j][k] = image[linewidth * i + bpp * j + k];

    stbi_image_free(image);

    return std::make_shared<ArrayTexture<Intensity<>>>(mat);
}

