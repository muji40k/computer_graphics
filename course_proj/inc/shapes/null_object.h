#ifndef _NULL_OBJECT_H_
#define _NULL_OBJECT_H_

#include "meta_object.h"

class NullObject : public MetaObject
{
    public:
        static const size_t ATTRI = 40;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~NullObject() override;

        virtual const Attribute &getAttribute(void) const override;

        virtual Intersection intersect(const Ray3<double> &ray) const override;
        virtual bool intersectBounding(const Ray3<double> &ray) const override;

        virtual double area(void) const override;

        virtual void apply(const Transform<double, 3> &transform) override;
        virtual void undo(const Transform<double, 3> &transform) override;
};

class CommonNullObjectException: public CommonMetaObjectException
{
    public:
        CommonNullObjectException(void) = default;
        CommonNullObjectException(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = "General null object exception")
            : CommonMetaObjectException(filename, line, function, message) {};
        ~CommonNullObjectException(void) = default;
};

#endif

