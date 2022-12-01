#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <memory>

#include "base_exception.h"

#include "object_primitive.h"
#include "point.h"
#include "ray.h"

class Polygon : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 20;
        static const Attribute &ATTRIBUTE(void);

    public:
        Polygon(const Point3<double>  &a      = Point3<double>(),
                const Point3<double>  &b      = Point3<double>({0, 1, 0}),
                const Point3<double>  &c      = Point3<double>({1, 0, 0}),
                const Normal3<double> &normal = Normal3<double>({0, 0, 1}));
        virtual ~Polygon();

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    // private:
    //     Vector3<double> sideV(size_t i) const;
    //     const Point3<double> &sideO(size_t i) const;

    private:
        std::shared_ptr<Point3<double>> center;
        std::shared_ptr<Vector3<double>> normals[3];
        double lnormalssqr[3];

        // std::shared_ptr<Point3<double>> a;
        // std::shared_ptr<Point3<double>> b;
        // std::shared_ptr<Point3<double>> c;
        std::shared_ptr<Normal3<double>> normal_in;
        std::shared_ptr<Normal3<double>> normal;
};

class DegeneratePolygonException : public BaseException
{
    public:
        DegeneratePolygonException(void) = default;
        DegeneratePolygonException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Polygon is degeneerate")
            : BaseException(filename, line, function, message) {};
        ~DegeneratePolygonException(void) = default;
};

#endif

