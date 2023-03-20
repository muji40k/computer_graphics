#ifndef _SPHERICAL_MAP_H_
#define _SPHERICAL_MAP_H_

#include "environment_map.h"

class SphericalMap : public EnvironmentMap
{
    public:
        SphericalMap(const std::shared_ptr<Texture<Intensity<>>> &texture,
                     const double &size);
        virtual ~SphericalMap(void) override;

        virtual Intensity<> map(const Ray3<double> &ray) const override;
};

#endif

