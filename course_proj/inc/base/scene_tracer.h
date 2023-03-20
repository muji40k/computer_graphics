#ifndef _SCENE_TRACER_H_
#define _SCENE_TRACER_H_

#include "scene.h"
#include "intersection.h"

class SceneTracer
{
    public:
        virtual ~SceneTracer(void) = 0;

        virtual Intersection trace(const Scene &scene, const Ray3<double> ray) const = 0;
};

#endif

