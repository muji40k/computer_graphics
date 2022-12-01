#ifndef _META_OBJECT_H_
#define _META_OBJECT_H_

#include "shape.h"

class MetaObject : public Shape
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~MetaObject() = 0;

        virtual const Attribute &getAttribute(void) const override;
};

#endif

