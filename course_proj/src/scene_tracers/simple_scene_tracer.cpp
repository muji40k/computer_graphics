#include "simple_scene_tracer.h"
#include "simple_shape_tracer.h"

SimpleSceneTracer::SimpleSceneTracer(void)
{
    this->shape_tracer = std::make_shared<SimpleShapeTracer>();
}

SimpleSceneTracer::~SimpleSceneTracer(void) {}

Intersection SimpleSceneTracer::trace(const Scene &scene, const Ray3<double> ray)
{
    Intersection inter, close;

    for (auto item : scene)
    {
        inter = this->shape_tracer->trace(*item, ray);

        if (inter && (!close || close.getT() > inter.getT()))
            close = inter;
    }

    return close;
}

