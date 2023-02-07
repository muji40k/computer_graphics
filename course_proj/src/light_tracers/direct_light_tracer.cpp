#include "direct_light_tracer.h"
#include "light_scene_tracer.h"

DirectLightTracer::DirectLightTracer(const Scene &scene) : scene(scene)
{
    auto lst = scene.getProperties(Lighting::ATTRIBUTE());

    for (auto property : lst)
    {
        this->lights.push_back(std::static_pointer_cast<const Lighting>(property));
        this->pcache.push_back(Point3<double>());

        Point3<double> &res = this->pcache.back();

        for (const Shape *current = &property->getTarget();
             nullptr != current;
             current = current->getParent())
            res.apply(current->getBasisTransform());
    }
}

DirectLightTracer::~DirectLightTracer(void) {}

std::list<light_trace_t> DirectLightTracer::trace(const Point3<double> &point)
{
    std::list<light_trace_t> out;
    LightSceneTracer tracer;
    Intersection inter;

    auto liter = this->lights.begin();
    auto piter = this->pcache.begin();
    Ray3<double> ray;
    ray.setOrigin(point);

    for (double distance; liter != this->lights.end(); liter++, piter++)
    {
        ray.setDirection(point > *piter);

        if (!tracer.trace(this->scene, ray))
        {
            distance = ray.getDirection().length();
            out.push_back({(*liter)->getEmission() / (distance * distance), ray.getDirection() / distance});
        }
    }

    return out;
}

