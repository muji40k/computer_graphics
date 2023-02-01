#ifndef _CONE_SMAPLER_H_
#define _CONE_SMAPLER_H_

#include "shape_sampler.h"

#include "vector.h"

class ConeSampler : public ShapeSampler
{
    public:
        ConeSampler(const Vector3<double> &normal = Vector3<double>({0, 0, 1}),
                    const Point3<double> &center = Point3<double>(),
                    double length = 5, double radius = 5);
        virtual ~ConeSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        void resetXY(void);

    private:
        Point3<double> base;
        Vector3<double> normal;
        Vector3<double> x;
        Vector3<double> y;
        double length;
        double radius;
};

#endif

