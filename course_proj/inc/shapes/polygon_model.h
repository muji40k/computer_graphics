#ifndef _POLYGON_MODEL_H_
#define _POLYGON_MODEL_H_

#include <list>

#include "base_exception.h"

#include "object.h"
#include "polygon.h"

#include "shape_sampler.h"

class PolygonModel : public Object
{
    public:
        static const size_t ATTRI = 12;
        static const Attribute &ATTRIBUTE(void);

    public:
        PolygonModel(void);
        virtual ~PolygonModel(void);

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

        void add(const Point3<double>  &a, const Point3<double>  &b,
                 const Point3<double>  &c, const Normal3<double> &normal);
        void remove(const size_t index);
        Polygon &get(const size_t index);
        const Polygon &get(const size_t index) const;
        size_t getAmount(void) const;

    private:
        void expandBounding(const Point3<double>  &a, const Point3<double>  &b,
                            const Point3<double>  &c);

    private:
        std::list<std::shared_ptr<Polygon>> lst;
        std::shared_ptr<ShapeSampler> sampler;
        std::shared_ptr<Bounding> bounding;
};

class CommonPolygonModelException: public CommonObjectException
{
    public:
        CommonPolygonModelException(void) = default;
        CommonPolygonModelException(const char *filename, const size_t line,
                              const char *function,
                              const char *message = "General polygon model exception")
            : CommonObjectException(filename, line, function, message) {};
        ~CommonPolygonModelException(void) = default;
};

class NullPointerPolygonModelException: public CommonPolygonModelException
{
    public:
        NullPointerPolygonModelException(void) = default;
        NullPointerPolygonModelException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Null pointer to a shape")
            : CommonPolygonModelException(filename, line, function, message) {};
        ~NullPointerPolygonModelException(void) = default;
};

class IndexViolationPolygonModelException: public CommonPolygonModelException
{
    public:
        IndexViolationPolygonModelException(void) = default;
        IndexViolationPolygonModelException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Requested shape index is above container size")
            : CommonPolygonModelException(filename, line, function, message) {};
        ~IndexViolationPolygonModelException(void) = default;
};

#endif

