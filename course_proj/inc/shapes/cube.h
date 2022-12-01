#ifndef _CUBE_H_
#define _CUBE_H_

#include <list>

#include "base_exception.h"

#include "parametric_model.h"
#include "plane.h"

class Cube : public ParametricModel
{
    public:
        static const size_t ATTRI = 31;
        static const Attribute &ATTRIBUTE(void);

    public:
        Cube(double lx, double ly, double lz);
        virtual ~Cube(void);

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::list<std::shared_ptr<Plane>> lst;
};

class DegenerateCubeException : public BaseException
{
    public:
        DegenerateCubeException(void) = default;
        DegenerateCubeException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Cube is degeneerate")
            : BaseException(filename, line, function, message) {};
        ~DegenerateCubeException(void) = default;
};

#endif

