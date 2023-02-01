#ifndef _BOUNDING_H_
#define _BOUNDING_H_

#include "transform.h"

#include <list>

#include "point.h"
#include "ray.h"

class Bounding : public Transformable<double>
{
    public:
        virtual ~Bounding(void) = 0;

        virtual void expand(const Point3<double> &point) = 0;
        virtual void expand(const std::list<Point3<double>> &points) = 0;
        virtual bool isInside(const Point3<double> &point) const = 0;
        virtual bool intersect(const Ray3<double> &ray) const = 0;

        virtual void apply(const Transform<double, 3> &transform) = 0;
        virtual void undo(const Transform<double, 3> &transform) = 0;
};

#endif

