#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "shape.h"

class Object : public Shape
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~Object() = 0;

        virtual const Attribute &getAttribute(void) const override;
};

class CommonObjectException: public CommonShapeException
{
    public:
        CommonObjectException(void) = default;
        CommonObjectException(const char *filename, const size_t line,
                              const char *function,
                              const char *message = "General object exception")
            : CommonShapeException(filename, line, function, message) {};
        ~CommonObjectException(void) = default;
};

#endif

