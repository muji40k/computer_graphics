#ifndef _SCATTERING_INFO_H_
#define _SCATTERING_INFO_H_

#include <list>

#include "attribute.h"
#include "base_exception.h"

#include "scattering_property.h"

class ScatteringInfo
{
    public:
        std::shared_ptr<ScatteringProperty> getProperty(const Attribute &attr) const;
        ScatteringInfo &setProperty(const std::shared_ptr<ScatteringProperty> property);

    private:
        std::list<std::shared_ptr<ScatteringProperty>> properties;
};

DEF_EX(CommonScatteringInfoException, BaseException,
       "General scattering info exception");
DEF_EX(DuplicateScatteringInfoException, CommonScatteringInfoException,
       "Duplicate property type");

#endif

