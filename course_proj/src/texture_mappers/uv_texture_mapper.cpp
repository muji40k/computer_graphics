#include "uv_texture_mapper.h"

UVTexturueMapper::~UVTexturueMapper(void) {};

Point2<double> UVTexturueMapper::map(const Intersection &intersection) const
{
    return intersection.getPointUV();
}

