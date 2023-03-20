#ifndef _UV_TEXTURE_MAPPER_H_
#define _UV_TEXTURE_MAPPER_H_

#include "texture_mapper.h"

class UVTexturueMapper : public TextureMapper
{
    public:
        virtual ~UVTexturueMapper(void) override;
        virtual Point2<double> map(const Intersection &intersection) const override;
};

#endif

