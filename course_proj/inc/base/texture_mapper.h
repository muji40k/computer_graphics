#ifndef _TEXTURE_MAPPER_H_
#define _TEXTURE_MAPPER_H_

#include "intersection.h"

class TextureMapper
{
    public:
        virtual ~TextureMapper(void) = 0;
        virtual Point2<double> map(const Intersection &intersection) const = 0;
};

#endif

