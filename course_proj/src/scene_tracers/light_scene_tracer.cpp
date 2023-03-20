#include "light_scene_tracer.h"
#include "light_shape_tracer.h"

LightSceneTracer::LightSceneTracer(void)
{
    this->shape_tracer = std::make_shared<LightShapeTracer>();
}

LightSceneTracer::~LightSceneTracer(void) {}

Intersection LightSceneTracer::trace(const Scene &scene, const Ray3<double> ray) const
{
    Intersection inter;

    for (auto item = scene.begin(); !inter && item != scene.end(); item++)
        inter = this->shape_tracer->trace(*std::const_pointer_cast<Shape>(*item), ray);

    return inter;
}

