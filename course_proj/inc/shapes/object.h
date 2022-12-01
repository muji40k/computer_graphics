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

#endif

