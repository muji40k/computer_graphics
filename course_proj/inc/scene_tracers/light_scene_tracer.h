#ifndef _LIGHT_SCENE_TRACER_H_
#define _LIGHT_SCENE_TRACER_H_

#include <memory>

#include "scene_tracer.h"
#include "shape_tracer.h"

class LightSceneTracer : public SceneTracer
{
    public:
        LightSceneTracer(void);
        virtual ~LightSceneTracer(void) override;
        virtual Intersection trace(const Scene &scene, const Ray3<double> ray) override;

    private:
        std::shared_ptr<ShapeTracer> shape_tracer;
};

#endif

