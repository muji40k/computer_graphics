#ifndef _SHAPE_SAMPLER_H_
#define _SHAPE_SAMPLER_H_

#include "transform.h"
#include "point.h"

class ShapeSampler : public Transformable<double, 3>
{
    public:
        virtual ~ShapeSampler(void) = 0;
        virtual bool isSamplabel(void) const = 0;
        virtual Point3<double> get(void) const = 0;
        virtual void append(const ShapeSampler *sampler) = 0;
};

#endif

