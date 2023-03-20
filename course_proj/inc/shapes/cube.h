#ifndef _CUBE_H_
#define _CUBE_H_

#include <list>

#include "base_exception.h"

#include "parametric_model.h"
#include "plane.h"
#include "bounding.h"

class Cube : public ParametricModel
{
    public:
        static const size_t ATTRI = 31;
        static const Attribute &ATTRIBUTE(void);

    public:
        Cube(double lx, double ly, double lz);
        virtual ~Cube(void);

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::list<std::shared_ptr<Plane>> lst;
        std::shared_ptr<Bounding> bounding;
        std::shared_ptr<ShapeSampler> sampler;
        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonCubeException : public CommonParametricModelException
{
    public:
        CommonCubeException(void) = default;
        CommonCubeException(const char *filename, const size_t line,
                            const char *function,
                            const char *message = "General cube exception")
            : CommonParametricModelException(filename, line, function, message) {};
        ~CommonCubeException(void) = default;
};

class DegenerateCubeException : public CommonCubeException
{
    public:
        DegenerateCubeException(void) = default;
        DegenerateCubeException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Cube is degeneerate")
            : CommonCubeException(filename, line, function, message) {};
        ~DegenerateCubeException(void) = default;
};

#endif

