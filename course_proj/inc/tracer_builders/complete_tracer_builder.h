#ifndef _COMPLETE_TRACER_BUILDER_H_
#define _COMPLETE_TRACER_BUILDER_H_

#include "base_complete_tracer_builder.h"

class CompleteTracerBuilder : public BaseCompleteTracerBuilder
{
    public:
        CompleteTracerBuilder(void);
        virtual ~CompleteTracerBuilder(void) override;
        virtual std::shared_ptr<BaseCompleteTracer> build(const TracerInfo &info) const override;
};

#endif

