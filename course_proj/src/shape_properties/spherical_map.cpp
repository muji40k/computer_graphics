#include "spherical_map.h"

#include "sphere.h"
#include "spherical_texture_mapper.h"

SphericalMap::SphericalMap(const std::shared_ptr<Texture<Intensity<>>> &texture,
                           const double &size)
    : EnvironmentMap(texture, size) {}

SphericalMap::~SphericalMap(void) {}

Intensity<> SphericalMap::map(const Ray3<double> &ray) const
{
    Intensity<> out;

    if (!ray)
        return out;

    Sphere sphere (this->size);
    Intersection inter = sphere.intersect(ray);

    if (inter)
    {
        Point2<double> mpoint = SphericalTextureMapper().map(inter);
        mpoint.x = 1 - mpoint.x;
        out = this->texture->getAt(mpoint);
    }

    return out;
}

