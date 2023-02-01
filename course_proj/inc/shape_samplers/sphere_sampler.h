#ifndef _SPHERE_SAMPLER_H_
#define _SPHERE_SAMPLER_H_

#include "shape_sampler.h"

class SphereSampler : public ShapeSampler
{
    public:
        SphereSampler(const Point3<double> &center = Point3<double>(),
                      double radius = 5);
        virtual ~SphereSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Point3<double> center;
        double radius;
        double rsqr;
};

#endif

