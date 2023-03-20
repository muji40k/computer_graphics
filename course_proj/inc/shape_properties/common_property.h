#ifndef _COMMON_PROPERTY_H_
#define _COMMON_PROPERTY_H_

#include "shape_property.h"

class CommonProperty : public ShapeProperty
{
    public:
        CommonProperty(void) : ShapeProperty(nullptr) {};
};

DEF_EX(CommonCommonPropertyException, CommonShapePropertyException,
       "General common shape property exception");

#endif

