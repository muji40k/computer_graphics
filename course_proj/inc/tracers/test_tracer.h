#ifndef _TEST_TRACER_H_
#define _TEST_TRACER_H_

#include "base_complete_tracer.h"

class TestTracer : public BaseCompleteTracer
{
    public:
        TestTracer(void);
        virtual ~TestTracer(void) override;
        virtual Intensity<> trace(const Scene &scene,
                                  const Ray3<double> &ray) const override;
};

#endif

