#ifndef _SHAPE_BUILDER_H_
#define _SHAPE_BUILDER_H_

#include <memory>

#include "shape.h"
#include "base_exception.h"

class BaseShapeBuilder
{
    public:
        virtual ~BaseShapeBuilder(void) = 0;
        virtual std::shared_ptr<Shape> build(void) = 0;
};

class CommonShapeBuilderException: public BaseException
{
    public:
        CommonShapeBuilderException(void) = default;
        CommonShapeBuilderException(const char *filename, const size_t line,
                                    const char *function,
                                    const char *message = "General shape builder exception")
            : BaseException(filename, line, function, message) {};
        ~CommonShapeBuilderException(void) = default;
};

#endif

