#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <memory>

#include "base_exception.h"

#include "point.h"
#include "normal.h"
#include "transform.h"

class Intersection;

#include "shape.h"

class Intersection : public Transformable<double, 3>
{
    public:
        Intersection(void);
        Intersection(const Shape *const shape,
                     const Point3<double> &point,
                     const Point2<double> &pointuv,
                     const Normal3<double> &normal,
                     double t,
                     const Transform<double, 3> &transform);
        virtual ~Intersection(void);

        operator bool(void) const;

        double getT(void) const;
        const Shape                *getShape(void)  const;
        const Point3<double>       &getPoint(void)  const;
        const Point3<double>       &getPointUV(void)  const;
        const Normal3<double>      &getNormal(void) const;
        const Transform<double, 3> &toGlobal(void)  const;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        bool valid;
        double t;

        Point3<double> point;
        Point2<double> pointuv;
        Normal3<double> normal;
        Transform<double, 3> transform;
        const Shape *shape = nullptr;
};

class NullPointerPolygonException: public BaseException
{
    public:
        NullPointerPolygonException(void) = default;
        NullPointerPolygonException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Null pointer to a polygon")
            : BaseException(filename, line, function, message) {};
        ~NullPointerPolygonException(void) = default;
};

#endif

