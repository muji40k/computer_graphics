#ifndef _SOLID_TEXTURE_H_
#define _SOLID_TEXTURE_H_

#include <memory>
#include "texture.h"

template <typename Type>
class SolidTexture : public Texture<Type>
{
    public:
        SolidTexture(const Type &value);
        virtual ~SolidTexture(void) override;
        virtual Type getAt(const Point2<double> &point) const override;

    private:
        std::shared_ptr<Type> value;
};

#include "solid_texture.hpp"

#endif

