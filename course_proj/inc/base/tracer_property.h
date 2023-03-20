#ifndef _TRACER_PROPERTY_H_
#define _TRACER_PROPERTY_H_

#include "attribute.h"

class TracerProperty
{
    public:
        static const size_t MAXATTR = 32;
        static const size_t ATTRI = 0;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~TracerProperty(void) = 0;
        virtual const Attribute &getAttribute(void) const;
};

#endif

