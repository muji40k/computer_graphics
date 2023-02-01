#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <memory>

#include "object_primitive.h"
#include "point.h"
#include "ray.h"

#include "bounding.h"

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

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Point3<double>> center;
        std::shared_ptr<Vector3<double>> normals[3];
        double lnormalssqr[3];
        double space;

        std::shared_ptr<Normal3<double>> normal_in;
        std::shared_ptr<Normal3<double>> normal;

        std::shared_ptr<Bounding> bounding;

        std::shared_ptr<ShapeSampler> sampler;
};

class CommonPolygonException: public CommonObjectPrimitiveException
{
    public:
        CommonPolygonException(void) = default;
        CommonPolygonException(const char *filename, const size_t line,
                               const char *function,
                               const char *message = "General polygon exception")
            : CommonObjectPrimitiveException(filename, line, function, message) {};
        ~CommonPolygonException(void) = default;
};

class DegeneratePolygonException : public CommonPolygonException
{
    public:
        DegeneratePolygonException(void) = default;
        DegeneratePolygonException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Polygon is degeneerate")
            : CommonPolygonException(filename, line, function, message) {};
        ~DegeneratePolygonException(void) = default;
};

#endif

