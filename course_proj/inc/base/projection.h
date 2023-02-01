#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include <cstdlib>
#include "ray.h"

class Projection
{
    public:
        virtual ~Projection(void) = 0;
        virtual Ray3<double> spawnRay(size_t i, size_t j) const = 0;
        virtual Ray3<double> sampleRay(size_t i, size_t j) const = 0;
};

#endif

