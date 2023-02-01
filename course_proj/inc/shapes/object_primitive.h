#ifndef _OBJECT_PRIMITIVE_H_
#define _OBJECT_PRIMITIVE_H_

#include "object.h"

class ObjectPrimitive : public Object
{
    public:
        static const size_t ATTRI = 10;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ObjectPrimitive() = 0;

        virtual const Attribute &getAttribute(void) const override;
};

class CommonObjectPrimitiveException: public CommonObjectException
{
    public:
        CommonObjectPrimitiveException(void) = default;
        CommonObjectPrimitiveException(const char *filename, const size_t line,
                              const char *function,
                              const char *message = "General object primitive exception")
            : CommonObjectException(filename, line, function, message) {};
        ~CommonObjectPrimitiveException(void) = default;
};

#endif

