#ifndef _PLANE_SAMPLER_H_
#define _PLANE_SAMPLER_H_

#include <memory>

#include "shape_sampler.h"

#include "transform.h"
#include "vector.h"

class PlaneSampler : public ShapeSampler
{
    public:
        PlaneSampler(double lx = 5, double ly = 5);
        virtual ~PlaneSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Vector3<double> x;
        Vector3<double> y;
        std::shared_ptr<Transform<double, 3>> transform;
};

#endif

