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

#endif

