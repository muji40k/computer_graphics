#ifndef _POLYGON_SAMPLER_H_
#define _POLYGON_SAMPLER_H_

#include "shape_sampler.h"
#include "vector.h"

class PolygonSampler : public ShapeSampler
{
    public:
        PolygonSampler(const Point3<double> &a = Point3<double>(),
                       const Point3<double> &b = Point3<double>({0, 1, 0}),
                       const Point3<double> &c = Point3<double>({1, 0, 0}));
        virtual ~PolygonSampler(void) override;
        virtual bool isSamplabel(void) const override;
        virtual Point3<double> get(void) const override;
        virtual void append(const ShapeSampler *sampler) override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Point3<double> base;
        Vector3<double> a;
        Vector3<double> b;
};

#endif

