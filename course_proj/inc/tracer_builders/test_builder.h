#ifndef _TEST_BUILDER_H_
#define _TEST_BUILDER_H_

#include "base_complete_tracer_builder.h"

class TestTracerBuilder : public BaseCompleteTracerBuilder
{
    public:
        TestTracerBuilder(void);
        virtual ~TestTracerBuilder(void) override;
        virtual std::shared_ptr<BaseCompleteTracer> build(const TracerInfo &info) const override;
};

#endif

