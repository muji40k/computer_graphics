#ifndef _COMPLETE_TRACER_H_
#define _COMPLETE_TRACER_H_

#include "base_complete_tracer.h"

class CompleteTracer : public BaseCompleteTracer
{
    public:
        CompleteTracer(size_t max_depth, size_t light_samples);
        virtual ~CompleteTracer(void) override;
        virtual Intensity<> trace(const Scene &scene,
                                  const Ray3<double> &ray) const override;

    public:
        const size_t max_depth;
        const size_t light_samples;
};

#endif

