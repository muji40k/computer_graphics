#ifndef _ARRAY_TEXTURE_H_
#define _ARRAY_TEXTURE_H_

#include <memory>
#include "texture.h"
#include "matrix.h"

template <typename Type>
class ArrayTexture : public Texture<Type>
{
    public:
        ArrayTexture(const Matrix<Type> &matrix);
        virtual ~ArrayTexture(void) override;
        virtual Type getAt(const Point2<double> &point) const override;

    private:
        std::shared_ptr<Matrix<Type>> matrix;
};

#include "array_texture.hpp"

#endif

