#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_

#include "bounding.h"

class BoundingSphere : public Bounding
{
    public:
        BoundingSphere(const Point3<double> &start);
        BoundingSphere(const BoundingSphere &bounding);
        BoundingSphere(BoundingSphere &&bounding);
        virtual ~BoundingSphere(void);

        virtual void expand(const Point3<double> &point) override;
        virtual void expand(const std::list<Point3<double>> &points) override;
        virtual bool isInside(const Point3<double> &point) const override;
        virtual bool intersect(const Ray3<double> &ray) const override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Point3<double> center;
        double radius;
        double radiussqr;
};

#endif

