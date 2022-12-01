#ifndef _PARAMETRIC_MODEL_H_
#define _PARAMETRIC_MODEL_H_

#include "object.h"

class ParametricModel : public Object
{
    public:
        static const size_t ATTRI = 11;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ParametricModel() = 0;

        virtual const Attribute &getAttribute(void) const override;
};

#endif

