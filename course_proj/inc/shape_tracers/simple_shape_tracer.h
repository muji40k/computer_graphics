#ifndef _SIMPLE_SHAPE_TRACER_H_
#define _SIMPLE_SHAPE_TRACER_H_

#include "shape_tracer.h"

class SimpleShapeTracer : public ShapeTracer
{
    public:
        virtual ~SimpleShapeTracer(void) override;

        virtual Intersection trace(const Shape &shape, const Ray3<double> ray) const override;
};


#endif

