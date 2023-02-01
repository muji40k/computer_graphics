#ifndef _SIMPLE_SHAPE_TRACER_H_
#define _SIMPLE_SHAPE_TRACER_H_

#include "shape.h"
#include "intersection.h"

#include "shape_tracer.h"

class SimpleShapeTracer : public ShapeTracer
{
    public:
        SimpleShapeTracer(void);
        virtual ~SimpleShapeTracer(void) override;

        virtual Intersection trace(const Shape &shape, const Ray3<double> ray) override;
};


#endif

