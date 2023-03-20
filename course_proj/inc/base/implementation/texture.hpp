#include "texture.h"
#include <float.h>

template <typename Type>
Texture<Type>::~Texture(void) {}

template <typename Type>
void Texture<Type>::check_bounding(const Point2<double> &point) const
{
    if (-FLT_EPSILON > point.x || 1 + FLT_EPSILON < point.x
        || -FLT_EPSILON > point.y || 1 + FLT_EPSILON < point.y)
        throw CALL_EX(OutOfBoundTextureException);
}

