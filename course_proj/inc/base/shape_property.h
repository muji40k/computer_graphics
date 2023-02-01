#ifndef _SHAPE_PROPERTY_H_
#define _SHAPE_PROPERTY_H_

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

class NullPointerShapePropertyException: public BaseException
{
    public:
        NullPointerShapePropertyException(void) = default;
        NullPointerShapePropertyException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Null pointer to a shape property")
            : BaseException(filename, line, function, message) {};
        ~NullPointerShapePropertyException(void) = default;
};

#endif

