#ifndef _MATERIAL_PROPERTY_H_
#define _MATERIAL_PROPERTY_H_

#include "base_exception.h"

#include "attribute.h"

class MaterialProperty
{
    public:
        static const size_t MAXATTR = 32;
        static const size_t ATTRI = 0;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~MaterialProperty(void) = 0;
        virtual const Attribute &getAttribute(void) const;
};

DEF_EX(CommonMaterialPropertyException, BaseException,
       "General material property exception");

#endif

