#ifndef _TRANSMISSION_FUNCTION_H_
#define _TRANSMISSION_FUNCTION_H_

#include "scattering_function.h"

class TransmissionFunction : public ScatteringFunction
{
    public:
        virtual ~TransmissionFunction(void) override = 0;
};

#endif

