#ifndef _SCATTERING_BUILDER_H_
#define _SCATTERING_BUILDER_H_

#include <memory>

#include "attribute.h"
#include "base_exception.h"

#include "scattering_function.h"
#include "scattering_info.h"

class ScatteringBuilder
{
    public:
        static const size_t MAXATTR = 32;
        static const size_t ATTRI = 0;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ScatteringBuilder(void) = 0;
        virtual std::shared_ptr<ScatteringFunction> build(const ScatteringInfo &info) const = 0;
        virtual const Attribute &getAttribute(void) const;
};

DEF_EX(CommonScatteringBuilderException, BaseException,
       "General scattering builder exception");
DEF_EX(NoReqiredPropertyScatteringBuilderException,
       CommonScatteringBuilderException, "");

#define NO_REQIRED_MSG(property) ("No reqired property: " #property)

#endif

