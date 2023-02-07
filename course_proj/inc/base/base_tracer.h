#ifndef _BASE_TRACER_H_
#define _BASE_TRACER_H_

#include "shape.h"
#include "intersection.h"

class BaseTracer
{
    public:
        virtual ~BaseTracer(void) = 0;

        virtual Intersection trace(const Shape &shape, const Ray3<double> ray) = 0;
};

#endif

