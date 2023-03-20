#ifndef _TRACER_MAX_DEPTH_H_
#define _TRACER_MAX_DEPTH_H_

#include "tracer_property.h"

class TracerMaxDepth : public TracerProperty
{
    public:
        static const size_t ATTRI = 1;
        static const Attribute &ATTRIBUTE(void);

    public:
        TracerMaxDepth(const size_t depth);
        virtual ~TracerMaxDepth(void) override;
        virtual const Attribute &getAttribute(void) const override;

        size_t getValue(void) const;

    private:
        size_t depth;
};

#endif

