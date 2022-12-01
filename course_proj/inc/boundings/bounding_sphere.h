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
        virtual std::list<Point3<double>> farest(const Point3<double> &point) const override;
        virtual std::list<Point3<double>> nearest(const Point3<double> &point) const override;
        virtual bool isInside(const Point3<double> &point) const override;
        virtual bool intersect(const Ray3<double> &ray) const override;

    private:
        Point3<double> center;
        double radius;
};

#endif

