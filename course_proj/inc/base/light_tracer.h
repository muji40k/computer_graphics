#ifndef _LIGHT_TRACERS_H_
#define _LIGHT_TRACERS_H_

#include <list>

#include "intensity.h"
#include "point.h"
#include "vector.h"

typedef struct
{
    Intensity<> intensity;
    Vector3<double> direction;
} light_trace_t;

class LightTracer
{
    public:
        virtual ~LightTracer(void) = 0;
        virtual std::list<light_trace_t> trace(const Point3<double> &point) const = 0;
};

#endif

