#ifndef _DEDICATED_PROPERTY_H_
#define _DEDICATED_PROPERTY_H_

#include "shape_property.h"

DEF_EX(CommonDedicatedPropertyException, CommonShapePropertyException,
       "General common shape property exception");
DEF_EX(NullShapePointerDedicatedPropertyException,
       CommonDedicatedPropertyException,
       "Attempt to set dedicated property to the root object");

class DedicatedProperty : public ShapeProperty
{
    public:
        DedicatedProperty(Shape *target) : ShapeProperty(target)
        {
            if (nullptr == target)
                throw CALL_EX(NullShapePointerDedicatedPropertyException);
        };
};

#endif

