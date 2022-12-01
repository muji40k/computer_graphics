#ifndef _PLANE_H_
#define _PLANE_H_

#include <memory>

#include "base_exception.h"

#include "object_primitive.h"
#include "point.h"
#include "ray.h"

class Plane : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 22;
        static const Attribute &ATTRIBUTE(void);

    public:
        Plane(const Point3<double> &center = Point3<double>(),
              const Vector3<double> &x = Vector3<double>({1, 0, 0}),
              const Vector3<double> &y = Vector3<double>({0, 1, 0}),
              double lx = 5, double ly = 5);
        Plane(const Normal3<double> &normal = Normal3<double>({0, 0, 1}),
              const Point3<double> &center = Point3<double>(),
              const Vector3<double> &x = Vector3<double>({1, 0, 0}),
              const Vector3<double> &y = Vector3<double>({0, 1, 0}),
              double lx = 5, double ly = 5);
        virtual ~Plane();

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Point3<double>> center;
        std::shared_ptr<Normal3<double>> normal;
        std::shared_ptr<Normal3<double>> normal_in;
        std::shared_ptr<Vector3<double>> vnormal;
        std::shared_ptr<Vector3<double>> x;
        std::shared_ptr<Vector3<double>> y;
        double lx;
        double ly;
        double ix;
        double iy;
};

class DegeneratePlaneException : public BaseException
{
    public:
        DegeneratePlaneException(void) = default;
        DegeneratePlaneException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Plane is degeneerate")
            : BaseException(filename, line, function, message) {};
        ~DegeneratePlaneException(void) = default;
};


#endif
