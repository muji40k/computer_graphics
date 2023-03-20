#ifndef _GRID_TEXTURE_MAPPER_H_
#define _GRID_TEXTURE_MAPPER_H_

#include "texture_mapper.h"

class GridTexturueMapper : public TextureMapper
{
    public:
        GridTexturueMapper(const TextureMapper &mapper, double scale_u, double scale_v);
        virtual ~GridTexturueMapper(void) override;
        virtual Point2<double> map(const Intersection &intersection) const override;

    private:
        const TextureMapper &mapper;
        double scales[2];
};

#endif

