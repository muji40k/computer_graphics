#include "spherical_texture_mapper.h"

SphericalTextureMapper::~SphericalTextureMapper(void) {}

Point2<double> SphericalTextureMapper::map(const Intersection &intersection) const
{
    Point2<double> out;

    if (!intersection.getPoint())
        return out;

    Vector3<double> dir = (Point3<double>() > intersection.getPoint()).normalised();

    out.x = 0.5 + atan2(-dir.x, -dir.z) / (2 * M_PI);
    out.y = acos(-dir.y) / M_PI;

    return out;
}

