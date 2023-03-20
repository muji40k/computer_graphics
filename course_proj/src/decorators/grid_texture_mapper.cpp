#include "grid_texture_mapper.h"

GridTexturueMapper::GridTexturueMapper(const TextureMapper &mapper,
                                       double scale_u, double scale_v)
    : mapper(mapper)
{
    scales[0] = fabs(scale_u);
    scales[1] = fabs(scale_v);
}

GridTexturueMapper::~GridTexturueMapper(void) {}

Point2<double> GridTexturueMapper::map(const Intersection &intersection) const
{
    Point2<double> uv = intersection.getPointUV();
    double tmp;

    for (size_t i = 0; uv.size() > i; i++)
        uv[i] = modf(this->scales[i] * uv[i], &tmp);

    return this->mapper.map(Intersection(intersection.getShape(),
                                         intersection.getPoint(),
                                         uv,
                                         intersection.getNormal(),
                                         intersection.getT(),
                                         intersection.toGlobal()));
}

