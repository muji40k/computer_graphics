#ifndef _DISK_SAMPLER_H_
#define _DISK_SAMPLER_H_

#include <memory>

#include "shape_sampler.h"

#include "transform.h"
#include "normal.h"

class DiskSampler : public ShapeSampler
{
    public:
        DiskSampler(double radius = 5);
        virtual ~DiskSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double radius;
        std::shared_ptr<Transform<double, 3>> transform;
};

#endif

