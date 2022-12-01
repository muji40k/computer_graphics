#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "base_exception.h"

#include "parametric_model.h"

class Sphere : public ParametricModel
{
    public:
        static const size_t ATTRI = 30;
        static const Attribute &ATTRIBUTE(void);

    public:
        Sphere(const Point3<double> &center = Point3<double>(),
               double radius = 5);
        virtual ~Sphere(void);

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Point3<double>> center;
        double radius;
        double radiussqr;
};

class DegenerateSphereException : public BaseException
{
    public:
        DegenerateSphereException(void) = default;
        DegenerateSphereException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Sphere is degeneerate")
            : BaseException(filename, line, function, message) {};
        ~DegenerateSphereException(void) = default;
};

#endif

