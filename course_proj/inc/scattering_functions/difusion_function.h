#ifndef _DIFUSION_FUNCTION_H_
#define _DIFUSION_FUNCTION_H_

#include "scattering_function.h"

class DifusionFunction : public ScatteringFunction
{
    public:
        virtual ~DifusionFunction(void) override = 0;
};

#endif

