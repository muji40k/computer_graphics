#include "direct_light_tracer.h"
#include "simple_shape_tracer.h"

DirectLightTracer::DirectLightTracer(const Scene &scene) : scene(scene)
{
    auto lst = scene.getProperties(Lighting::ATTRIBUTE());

    for (auto property : lst)
    {
        this->lights.push_back(std::static_pointer_cast<const Lighting>(property));

        Point3<double> res;

        for (const Shape *current = &property->getTarget();
             nullptr != current;
             current = current->getParent())
            res.apply(current->getBasisTransform());

        this->pcache.push_back(res);
    }
}

DirectLightTracer::~DirectLightTracer(void) {}

std::list<light_trace_t> DirectLightTracer::trace(const Point3<double> &point)
{
    std::list<light_trace_t> out;
    SimpleShapeTracer tracer;
    Intersection inter;

    auto liter = this->lights.begin();
    auto piter = this->pcache.begin();
    Ray3<double> ray;
    ray.setOrigin(point);

    for (double distance; liter != this->lights.end(); liter++, piter++)
    {
        ray.setDirection(point > *piter);
        auto siter = this->scene.begin();
        inter = Intersection();
        bool i = false;

        for (; !i && siter != this->scene.end(); siter++)
        {
            inter = tracer.trace(*(*siter), ray);

            if (inter
                && 1 - FLT_EPSILON > inter.getT()
                && FLT_EPSILON < inter.getT())
                i = true;
        }

        if (!i)
        {
            distance = ray.getDirection().length();
            out.push_back({(*liter)->getEmission() / (distance * distance), ray.getDirection() / distance});
        }
    }

    return out;
}

