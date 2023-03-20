#ifndef _SHAPE_PROPERTY_H_
#define _SHAPE_PROPERTY_H_

#include "base_exception.h"

#include "shape.h"
#include "attribute.h"

class ShapeProperty
{
    public:
        static const size_t ATTRI = 0;
        static const size_t MAXATTR = 32;
        static const Attribute &ATTRIBUTE(void);

    public:
        ShapeProperty(Shape *target);
        virtual ~ShapeProperty(void) = 0;
        Shape &getTarget(void);
        const Shape &getTarget(void) const;
        virtual const Attribute &getAttribute(void) const;

    private:
        Shape *target = nullptr;
};

DEF_EX(CommonShapePropertyException, BaseException,
       "General shape property exception");

#endif

