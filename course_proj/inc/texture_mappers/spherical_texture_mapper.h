#ifndef _SPHERICAL_TEXTURE_MAPPER_H_
#define _SPHERICAL_TEXTURE_MAPPER_H_

#include "texture_mapper.h"

class SphericalTextureMapper : public TextureMapper
{
    public:
        virtual ~SphericalTextureMapper(void) override;
        virtual Point2<double> map(const Intersection &intersection) const override;
};

#endif

