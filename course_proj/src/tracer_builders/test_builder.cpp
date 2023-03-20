#include "test_builder.h"

#include "test_tracer.h"

TestTracerBuilder::TestTracerBuilder(void) {}

TestTracerBuilder::~TestTracerBuilder(void) {}

std::shared_ptr<BaseCompleteTracer> TestTracerBuilder::build(const TracerInfo &) const
{
    return std::make_shared<TestTracer>();
}

