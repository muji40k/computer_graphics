#ifndef _SCATTERING_FUNCTION_H_
#define _SCATTERING_FUNCTION_H_

#include "attribute.h"

#include "intensity.h"
#include "intersection.h"
#include "vector.h"

class ScatteringFunction
{
    public:
        virtual ~ScatteringFunction(void) = 0;
        virtual Intensity<> apply(const Vector3<double> &in,
                                  const Vector3<double> &out) const = 0;
};

#endif

