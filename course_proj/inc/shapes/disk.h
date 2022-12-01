#ifndef _DISK_H_
#define _DISK_H_

#include <memory>

#include "base_exception.h"

#include "object_primitive.h"
#include "point.h"
#include "ray.h"

class Disk : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 21;
        static const Attribute &ATTRIBUTE(void);

    public:
        Disk(const Point3<double> &center,
             const Normal3<double> &normal,
             double radius);
        virtual ~Disk();

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        std::shared_ptr<Point3<double>> center;
        std::shared_ptr<Normal3<double>> normal;
        double radius;
};

class NegativeRadiusDiskException : public BaseException
{
    public:
        NegativeRadiusDiskException(void) = default;
        NegativeRadiusDiskException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Negative radius given")
            : BaseException(filename, line, function, message) {};
        ~NegativeRadiusDiskException(void) = default;
};

#endif

