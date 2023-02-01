#ifndef _POLYGON_MODEL_H_
#define _POLYGON_MODEL_H_

#include <list>

#include "base_exception.h"

#include "object.h"
#include "polygon.h"

class PolygonModel : public Object
{
    public:
        static const size_t ATTRI = 12;
        static const Attribute &ATTRIBUTE(void);

    public:
        using iterator = list<Polygon *>::iterator;
        using const_iterator = list<Polygon *>::const_iterator;

        virtual ~PolygonModel();

        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual const Attribute &getAttribute(void) const override;
        virtual Intersection intersect(const Ray3<double> &ray) const override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;

        void add(Polygon *shape);
        void remove(Polygon *shape);
        void remove(const size_t index);
        void remove(iterator &it);
        Polygon &get(const size_t index);
        const Polygon &get(const size_t index) const;
        size_t getAmount(void) const;

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void) const;
        const_iterator end(void) const;
        const_iterator cbegin(void) const;
        const_iterator cend(void) const;

    private:
        std::list<Polygon *> lst;
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

