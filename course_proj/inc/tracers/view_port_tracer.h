#ifndef _VIEW_PORT_TRACER_H_
#define _VIEW_PORT_TRACER_H_

#include "base_tracer.h"

class ViewPortTracer : public BaseTracer
{
    public:
        ViewPortTracer(void);
        virtual ~ViewPortTracer(void) override;
        virtual Intensity<> trace(const Scene &scene,
                                  const Ray3<double> &ray) const override;
};

#endif

