#ifndef _CONE_H_
#define _CONE_H_

#include <memory>

#include "parametric_model.h"
#include "disk.h"

#include "bounding.h"

class Cone : public ParametricModel
{
    public:
        static const size_t ATTRI = 33;
        static const Attribute &ATTRIBUTE(void);

    public:
        Cone(double length, double radius);
        virtual ~Cone() override;

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        Intersection coneIntersect(const Ray3<double> &ray) const;

    private:
        double length;
        double radius;
        double rsqr;
        double lsqr;
        std::shared_ptr<Bounding> bounding;
        std::shared_ptr<Disk> cap;
        std::shared_ptr<ShapeSampler> sampler;
        std::shared_ptr<ShapeSampler> cone_sampler;
        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonConeException : public CommonParametricModelException
{
    public:
        CommonConeException(void) = default;
        CommonConeException(const char *filename, const size_t line,
                            const char *function,
                            const char *message = "General cone exception")
            : CommonParametricModelException(filename, line, function, message) {};
        ~CommonConeException(void) = default;
};

class DegenerateConeException : public CommonConeException
{
    public:
        DegenerateConeException(void) = default;
        DegenerateConeException(const char *filename, const size_t line,
                                const char *function,
                                const char *message = "Given tube is degenerate")
            : CommonConeException(filename, line, function, message) {};
        ~DegenerateConeException(void) = default;
};

#endif

