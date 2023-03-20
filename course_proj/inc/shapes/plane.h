#ifndef _PLANE_H_
#define _PLANE_H_

#include <memory>

#include "base_exception.h"

#include "object_primitive.h"
#include "point.h"
#include "ray.h"

#include "bounding.h"

class Plane : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 22;
        static const Attribute &ATTRIBUTE(void);

    public:
        Plane(double lx = 5, double lz = 5, bool flip_normal = false);
        virtual ~Plane();

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double lx;
        double lz;
        bool flip;
        std::shared_ptr<Bounding> bounding;
        double space;
        std::shared_ptr<ShapeSampler> sampler;
        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonPlaneException : public CommonObjectPrimitiveException
{
    public:
        CommonPlaneException(void) = default;
        CommonPlaneException(const char *filename, const size_t line,
                            const char *function,
                            const char *message = "General plane exception")
            : CommonObjectPrimitiveException(filename, line, function, message) {};
        ~CommonPlaneException(void) = default;
};

class DegeneratePlaneException : public CommonPlaneException
{
    public:
        DegeneratePlaneException(void) = default;
        DegeneratePlaneException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Plane is degeneerate")
            : CommonPlaneException(filename, line, function, message) {};
        ~DegeneratePlaneException(void) = default;
};

#endif

