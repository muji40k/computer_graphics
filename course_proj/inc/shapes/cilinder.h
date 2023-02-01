#ifndef _CILINDER_H_
#define _CILINDER_H_

#include "parametric_model.h"
#include "tube.h"
#include "disk.h"

class Cilinder : public ParametricModel
{
    public:
        static const size_t ATTRI = 32;
        static const Attribute &ATTRIBUTE(void);

    public:
        Cilinder(const Vector3<double> &normal = Vector3<double>({0, 0, 1}),
                 const Point3<double> &center = Point3<double>(),
                 double length = 5, double radius = 5);
        virtual ~Cilinder() override;

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Tube> tube;
        std::shared_ptr<Disk> top;
        std::shared_ptr<Disk> bottom;
        std::shared_ptr<ShapeSampler> sampler;
};

class CommonCilinderException: public CommonParametricModelException
{
    public:
        CommonCilinderException(void) = default;
        CommonCilinderException(const char *filename, const size_t line,
                                       const char *function,
                                       const char *message = "General cilinder exception")
            : CommonParametricModelException(filename, line, function, message) {};
        ~CommonCilinderException(void) = default;
};

#endif

