#ifndef _BASE_COMPLETE_TRACER_BUILDER_H_
#define _BASE_COMPLETE_TRACER_BUILDER_H_

#include <memory>

#include "base_complete_tracer.h"
#include "tracer_info.h"

class BaseCompleteTracerBuilder
{
    public:
        virtual ~BaseCompleteTracerBuilder(void) = 0;
        virtual std::shared_ptr<BaseCompleteTracer> build(const TracerInfo &info) const = 0;
};

DEF_EX(CommonBaseCompleteTracerBuilderException, BaseException,
       "General scattering builder exception");
DEF_EX(NoReqiredPropertyBaseCompleteTracerBuilderException,
       CommonBaseCompleteTracerBuilderException, "");

#define NO_REQIRED_MSG(property) ("No reqired property: " #property)

#endif

