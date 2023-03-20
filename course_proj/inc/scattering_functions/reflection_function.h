#ifndef _REFLECTION_FUNCTION_H_
#define _REFLECTION_FUNCTION_H_

#include "scattering_function.h"

class ReflectionFunction : public ScatteringFunction
{
    public:
        virtual ~ReflectionFunction(void) override = 0;
};

#endif

