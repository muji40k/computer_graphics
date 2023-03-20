#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "parametric_model.h"

#include "bounding.h"

class Sphere : public ParametricModel
{
    public:
        static const size_t ATTRI = 30;
        static const Attribute &ATTRIBUTE(void);

    public:
        Sphere(double radius);
        virtual ~Sphere(void);

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double radius;
        double radiussqr;
        std::shared_ptr<Bounding> bounding;
        std::shared_ptr<ShapeSampler> sampler;

        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonSphereException: public CommonParametricModelException
{
    public:
        CommonSphereException(void) = default;
        CommonSphereException(const char *filename, const size_t line,
                              const char *function,
                              const char *message = "General sphere exception")
            : CommonParametricModelException(filename, line, function, message) {};
        ~CommonSphereException(void) = default;
};

class DegenerateSphereException : public CommonSphereException
{
    public:
        DegenerateSphereException(void) = default;
        DegenerateSphereException(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = "Sphere is degeneerate")
            : CommonSphereException(filename, line, function, message) {};
        ~DegenerateSphereException(void) = default;
};

#endif

