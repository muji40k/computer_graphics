#ifndef _TRACER_INFO_H_
#define _TRACER_INFO_H_

#include <list>

#include "attribute.h"
#include "base_exception.h"

#include "tracer_property.h"

class TracerInfo
{
    public:
        std::shared_ptr<TracerProperty> getProperty(const Attribute &attr) const;
        TracerInfo &setProperty(const std::shared_ptr<TracerProperty> property);

    private:
        std::list<std::shared_ptr<TracerProperty>> properties;
};

DEF_EX(CommonTracerInfoException, BaseException,
       "General scattering info exception");
DEF_EX(DuplicateTracerInfoException, CommonTracerInfoException,
       "Duplicate property type");


#endif

