#include "image_array_texture_builder.h"

#include "matrix.h"

#include "intensity.h"
#include "array_texture.h"
#include "vector.h"

#include "stb_image.h"

template <>
std::shared_ptr<Texture<Intensity<>>> ImageArrayTextureBuilder<Intensity<>>::build(void)
{
    static const double inv255 = (double)1 / 255;
    int width, height, bpp;

    if (EXIT_SUCCESS == stbi_info(this->filename, &width, &height, &bpp))
        throw CALL_EX(NoFileArrayTextureBuilderException);

    uint8_t* image = stbi_load(this->filename, &width, &height, &bpp, 0);

    if (NULL == image)
        throw CALL_EX(AllocationImageArrayTextureBuilderException);

    int lim = (bpp > 3) ? 3 : bpp;
    int linewidth = bpp * width;

    Matrix<Intensity<>> mat ((size_t)height, (size_t)width);

    for (int i = 0; height > i; i++)
        for (int j = 0; width > j; j++)
            for (int k = 0; lim > k; k++)
                mat[i][j][k] = (double)image[linewidth * i + bpp * j + k] * inv255;

    stbi_image_free(image);

    return std::make_shared<ArrayTexture<Intensity<>>>(mat);
}

template <>
std::shared_ptr<Texture<Vector3<double>>> ImageArrayTextureBuilder<Vector3<double>>::build(void)
{
    int width, height, bpp;

    if (EXIT_SUCCESS == stbi_info(this->filename, &width, &height, &bpp))
        throw CALL_EX(NoFileArrayTextureBuilderException);

    uint8_t* image = stbi_load(this->filename, &width, &height, &bpp, 0);

    if (NULL == image)
        throw CALL_EX(AllocationImageArrayTextureBuilderException);

    int lim = (bpp > 3) ? 3 : bpp;
    int linewidth = bpp * width;

    Matrix<Vector3<double>> mat ((size_t)height, (size_t)width);

    for (int i = 0; height > i; i++)
        for (int j = 0; width > j; j++)
        {
            Vector3<double> current ({1, 1, 1});

            for (int k = 0; lim > k; k++)
                current[k] = (double)image[linewidth * i + bpp * j + k] / 255;

            mat[i][j] = current;
        }

    stbi_image_free(image);

    return std::make_shared<ArrayTexture<Vector3<double>>>(mat);
}

