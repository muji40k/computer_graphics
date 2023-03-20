#ifndef _TUBE_H_
#define _TUBE_H_

#include <memory>

#include "object_primitive.h"

#include "bounding.h"

class Tube : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 23;
        static const Attribute &ATTRIBUTE(void);

    public:
        Tube(double length, double radius);
        virtual ~Tube() override;

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double length;
        double radius;
        double rsqr;
        std::shared_ptr<Bounding> bounding;
        std::shared_ptr<ShapeSampler> sampler;
        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonTubeException : public CommonObjectPrimitiveException
{
    public:
        CommonTubeException(void) = default;
        CommonTubeException(const char *filename, const size_t line,
                            const char *function,
                            const char *message = "General tube exception")
            : CommonObjectPrimitiveException(filename, line, function, message) {};
        ~CommonTubeException(void) = default;
};

class DegenerateTubeException : public CommonTubeException
{
    public:
        DegenerateTubeException(void) = default;
        DegenerateTubeException(const char *filename, const size_t line,
                                const char *function,
                                const char *message = "Given tube is degenerate")
            : CommonTubeException(filename, line, function, message) {};
        ~DegenerateTubeException(void) = default;
};

#endif

