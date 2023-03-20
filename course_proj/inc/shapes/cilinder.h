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
        Cilinder(double length, double radius);
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
        std::shared_ptr<Transform<double, 3>> transform_local;
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

