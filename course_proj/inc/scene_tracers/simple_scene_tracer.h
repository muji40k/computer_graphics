#ifndef _SIMPLE_SCENE_TRACER_H_
#define _SIMPLE_SCENE_TRACER_H_

#include <memory>

#include "scene_tracer.h"
#include "shape_tracer.h"

class SimpleSceneTracer : public SceneTracer
{
    public:
        SimpleSceneTracer(void);
        virtual ~SimpleSceneTracer(void) override;
        virtual Intersection trace(const Scene &scene, const Ray3<double> ray) override;

    private:
        std::shared_ptr<ShapeTracer> shape_tracer;
};

#endif

