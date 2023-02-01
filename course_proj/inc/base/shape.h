#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <list>
#include <memory>

#include "base_exception.h"

#include "attribute.h"

#include "transform.h"
#include "ray.h"

class Shape;

#include "intersection.h"
#include "shape_sampler.h"

class Shape : public Transformable<double, 3>
{
    public:
        static const size_t ATTRI = 0;
        static const size_t MAXATTR = 50;
        static const Attribute &ATTRIBUTE(void);

    public:
        using iterator = list<Shape *>::iterator;
        using const_iterator = list<Shape *>::const_iterator;

        Shape(Shape *parent = nullptr);

        virtual ~Shape() = 0;

        void add(Shape *shape);
        void remove(Shape *shape);
        void remove(const size_t index);
        void remove(iterator &it);
        Shape &get(const size_t index);
        const Shape &get(const size_t index) const;
        size_t getAmount(void) const;

        virtual const Attribute &getAttribute(void) const;
        virtual Intersection intersect(const Ray3<double> &ray) const = 0;

        void setParent(Shape *parent);
        Shape *getParent(void);
        const Shape *getParent(void) const;

        virtual bool intersectBounding(const Ray3<double> &ray) const = 0;

        void applyBasis(const Transform<double, 3> &transform);
        void undoBasis(const Transform<double, 3> &transform);
        void resetBasis(void);
        Transform<double, 3> &getBasisTransform(void);
        const Transform<double, 3> &getBasisTransform(void) const;

        virtual double area(void) const = 0;

        virtual const ShapeSampler &getSampler(void) const = 0;

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void) const;
        const_iterator end(void) const;
        const_iterator cbegin(void) const;
        const_iterator cend(void) const;

    private:
        std::list<Shape *> structure;
        Shape *parent;

    protected:
        std::shared_ptr<Transform<double, 3>> transform_global;
};

class CommonShapeException: public BaseException
{
    public:
        CommonShapeException(void) = default;
        CommonShapeException(const char *filename, const size_t line,
                             const char *function,
                             const char *message = "General shape exception")
            : BaseException(filename, line, function, message) {};
        ~CommonShapeException(void) = default;
};

class NullPointerShapeException: public CommonShapeException
{
    public:
        NullPointerShapeException(void) = default;
        NullPointerShapeException(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = "Null pointer to a shape")
            : CommonShapeException(filename, line, function, message) {};
        ~NullPointerShapeException(void) = default;
};

class IndexViolationShapeException: public CommonShapeException
{
    public:
        IndexViolationShapeException(void) = default;
        IndexViolationShapeException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Requested shape index is above container size")
            : CommonShapeException(filename, line, function, message) {};
        ~IndexViolationShapeException(void) = default;
};

#endif



