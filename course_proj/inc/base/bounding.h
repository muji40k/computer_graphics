#ifndef _BOUNDING_H_
#define _BOUNDING_H_

#include <list>

#include "point.h"
#include "ray.h"

class Bounding
{
    public:
        virtual ~Bounding(void) = 0;

        virtual void expand(const Point3<double> &point) = 0;
        virtual void expand(const std::list<Point3<double>> &points) = 0;
        virtual std::list<Point3<double>> farest(const Point3<double> &point) const = 0;
        virtual std::list<Point3<double>> nearest(const Point3<double> &point) const = 0;
        virtual bool isInside(const Point3<double> &point) const = 0;
        virtual bool intersect(const Ray3<double> &ray) const = 0;
};

#endif

