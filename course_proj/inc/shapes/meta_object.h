#ifndef _META_OBJECT_H_
#define _META_OBJECT_H_

#include "shape.h"
#include "none_sampler.h"

class MetaObject : public Shape
{
    public:
        static const size_t ATTRI = 2;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~MetaObject() = 0;

        virtual const Attribute &getAttribute(void) const override;

        virtual const ShapeSampler &getSampler(void) const override;

    private:
        NoneSampler sampler;
};

class CommonMetaObjectException: public CommonShapeException
{
    public:
        CommonMetaObjectException(void) = default;
        CommonMetaObjectException(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = "General meta object exception")
            : CommonShapeException(filename, line, function, message) {};
        ~CommonMetaObjectException(void) = default;
};

#endif

