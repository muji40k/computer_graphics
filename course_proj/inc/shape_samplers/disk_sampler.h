#ifndef _DISK_SAMPLER_H_
#define _DISK_SAMPLER_H_

#include "shape_sampler.h"
#include "normal.h"

class DiskSampler : public ShapeSampler
{
    public:
        DiskSampler(const Point3<double> &center,
                    const Vector3<double> &normal,
                    double radius);
        virtual ~DiskSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        void resetXY(void);

    private:
        Point3<double> center;
        Vector3<double> normal;
        Vector3<double> x;
        Vector3<double> y;
        double radius;
};

#endif

