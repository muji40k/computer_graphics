#ifndef _SPHERE_SAMPLER_H_
#define _SPHERE_SAMPLER_H_

#include <memory>

#include "shape_sampler.h"

#include "transform.h"

class SphereSampler : public ShapeSampler
{
    public:
        SphereSampler(double radius = 5);
        virtual ~SphereSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double radius;
        double rsqr;
        std::shared_ptr<Transform<double, 3>> transform;
};

#endif

