#ifndef _NONE_SAMPLER_H_
#define _NONE_SAMPLER_H_

#include "shape_sampler.h"

class NoneSampler : public ShapeSampler
{
    public:
        NoneSampler(void) {};
        virtual ~NoneSampler(void) override {};
        virtual bool isSamplabel(void) const override { return false; };
        virtual Point3<double> get(void) const override { return Point3<double> (); };
        virtual void append(const ShapeSampler *) override {};

        virtual void apply(const Transform<double, 3> &) override {};
        virtual void undo(const Transform<double, 3> &) override {};

};

#endif

