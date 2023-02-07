#ifndef _LIGHT_SHAPE_TRACER_H_
#define _LIGHT_SHAPE_TRACER_H_

#include "shape.h"
#include "intersection.h"

#include "shape_tracer.h"

class LightShapeTracer : public ShapeTracer
{
    public:
        LightShapeTracer(void);
        virtual ~LightShapeTracer(void) override;

        virtual Intersection trace(const Shape &shape, const Ray3<double> ray) override;
};


#endif
