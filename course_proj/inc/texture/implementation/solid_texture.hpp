#include "solid_texture.h"

template <typename Type>
SolidTexture<Type>::SolidTexture(const Type &value)
{
    this->value = std::make_shared<Type>(value);
}

template <typename Type>
SolidTexture<Type>::~SolidTexture(void) {}

template <typename Type>
Type SolidTexture<Type>::getAt(const Point2<double> &point) const
{
    this->check_bounding(point);

    return *this->value;
}

