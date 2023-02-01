#ifndef _SHAPE_TRACER_H_
#define _SHAPE_TRACER_H_

#include "shape.h"
#include "intersection.h"

class ShapeTracer
{
    public:
        virtual ~ShapeTracer(void) = 0;

        virtual Intersection trace(const Shape &shape, const Ray3<double> ray) = 0;
};

#endif

