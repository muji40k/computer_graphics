#ifndef _BASE_TRACER_H_
#define _BASE_TRACER_H_

#include "intensity.h"
#include "ray.h"
#include "scene.h"

class BaseTracer
{
    public:
        virtual ~BaseTracer(void) = 0;
        virtual Intensity<> trace(const Scene &scene,
                                  const Ray3<double> &ray) const = 0;
};

#endif

