#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <list>
#include <memory>

#include "base_exception.h"

#include "attribute.h"

#include "transform.h"
#include "ray.h"
#include "basis.h"

class Shape;

#include "intersection.h"

class Shape : public Transformable<double, 3>
{
    public:
        static const size_t ATTRI = 0;
        static const size_t MAXATTR = 32;
        static const Attribute &ATTRIBUTE(void);

    public:
        // TODO Собственный итератор для ссылок
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
        virtual Intersection intersect(const Ray3<double> &ray) const;

        void setParent(Shape *parent);
        Shape &getParent(void);
        const Shape &getParent(void) const;

        // #?# getBounding(void) const;
        // #?# getBoundingOuter(void) const;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

        void applyBasis(const Transform<double, 3> &transform);
        void undoBasis(const Transform<double, 3> &transform);
        void resetBasis(void);

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

class NullPointerShapeException: public BaseException
{
    public:
        NullPointerShapeException(void) = default;
        NullPointerShapeException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Null pointer to a shape")
            : BaseException(filename, line, function, message) {};
        ~NullPointerShapeException(void) = default;
};

class IndexViolationShapeException: public BaseException
{
    public:
        IndexViolationShapeException(void) = default;
        IndexViolationShapeException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Requested shape index is above container size")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationShapeException(void) = default;
};

#endif



