#include "complete_tracer_builder.h"

#include "complete_tracer.h"

#include "tracer_max_depth.h"
#include "tracer_light_samples.h"

CompleteTracerBuilder::CompleteTracerBuilder(void) {}

CompleteTracerBuilder::~CompleteTracerBuilder(void) {}

std::shared_ptr<BaseCompleteTracer> CompleteTracerBuilder::build(const TracerInfo &info) const
{
    std::shared_ptr<TracerMaxDepth> max_depth = \
        std::static_pointer_cast<TracerMaxDepth>(info.getProperty(TracerMaxDepth::ATTRIBUTE()));
    std::shared_ptr<TracerLightSamples> light_samples = \
        std::static_pointer_cast<TracerLightSamples>(info.getProperty(TracerLightSamples::ATTRIBUTE()));

    if (nullptr == max_depth)
        throw CALL_EX_MSG(NoReqiredPropertyBaseCompleteTracerBuilderException,
                          NO_REQIRED_MSG(TracerMaxDepth));

    if (nullptr == light_samples)
        throw CALL_EX_MSG(NoReqiredPropertyBaseCompleteTracerBuilderException,
                          NO_REQIRED_MSG(TracerLightSamples));

    return std::make_shared<CompleteTracer>(max_depth->getValue(),
                                            light_samples->getValue());
}

