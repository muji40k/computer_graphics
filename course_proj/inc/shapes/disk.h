#ifndef _DISK_H_
#define _DISK_H_

#include <memory>

#include "object_primitive.h"
#include "bounding.h"
#include "point.h"
#include "ray.h"

class Disk : public ObjectPrimitive
{
    public:
        static const size_t ATTRI = 21;
        static const Attribute &ATTRIBUTE(void);

    public:
        Disk(double radius, bool flip_normal = false);
        virtual ~Disk();

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

    private:
        double radius;
        double rsqr;
        bool flip;
        std::shared_ptr<Bounding> bounding;
        std::shared_ptr<ShapeSampler> sampler;

        std::shared_ptr<Transform<double, 3>> transform_local;
};

class CommonDiskException: public CommonObjectPrimitiveException
{
    public:
        CommonDiskException(void) = default;
        CommonDiskException(const char *filename, const size_t line,
                            const char *function,
                            const char *message = "General disk exception")
            : CommonObjectPrimitiveException(filename, line, function, message) {};
        ~CommonDiskException(void) = default;
};

class NegativeRadiusDiskException : public CommonDiskException
{
    public:
        NegativeRadiusDiskException(void) = default;
        NegativeRadiusDiskException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Negative radius given")
            : CommonDiskException(filename, line, function, message) {};
        ~NegativeRadiusDiskException(void) = default;
};

#endif

