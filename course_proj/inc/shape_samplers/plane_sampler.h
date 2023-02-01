#ifndef _PLANE_SAMPLER_H_
#define _PLANE_SAMPLER_H_

#include "shape_sampler.h"
#include "vector.h"

class PlaneSampler : public ShapeSampler
{
    public:
        PlaneSampler(const Point3<double> &center = Point3<double>(),
                     const Vector3<double> &x = Vector3<double>({1, 0, 0}),
                     const Vector3<double> &y = Vector3<double>({0, 1, 0}),
                     double lx = 5, double ly = 5);
        virtual ~PlaneSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Point3<double> base;
        Vector3<double> x;
        Vector3<double> y;
};

#endif

