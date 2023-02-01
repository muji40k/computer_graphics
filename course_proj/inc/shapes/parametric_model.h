#ifndef _PARAMETRIC_MODEL_H_
#define _PARAMETRIC_MODEL_H_

#include "object.h"

class ParametricModel : public Object
{
    public:
        static const size_t ATTRI = 11;
        static const Attribute &ATTRIBUTE(void);

    public:
        virtual ~ParametricModel() = 0;

        virtual const Attribute &getAttribute(void) const override;
};

class CommonParametricModelException: public CommonObjectException
{
    public:
        CommonParametricModelException(void) = default;
        CommonParametricModelException(const char *filename, const size_t line,
                                       const char *function,
                                       const char *message = "General parametric model exception")
            : CommonObjectException(filename, line, function, message) {};
        ~CommonParametricModelException(void) = default;
};

#endif

