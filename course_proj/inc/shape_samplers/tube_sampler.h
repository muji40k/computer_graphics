#ifndef _TUBE_SMAPLER_H_
#define _TUBE_SMAPLER_H_

#include <memory>

#include "shape_sampler.h"

#include "transform.h"
#include "vector.h"

class TubeSampler : public ShapeSampler
{
    public:
        TubeSampler(double length = 5, double radius = 5);
        virtual ~TubeSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double length;
        double radius;
        std::shared_ptr<Transform<double, 3>> transform;
};

#endif

