#include "sampling_light_tracer.h"
#include "light_scene_tracer.h"

SamplingLightTracer::SamplingLightTracer(const Scene &scene, size_t samples)
    : samples(samples), scene(scene)
{
    auto lst = scene.getProperties(Lighting::ATTRIBUTE());

    for (auto property : lst)
    {
        if (property->getTarget().getSampler().isSamplabel())
        {
            this->sample_lights.push_back(std::static_pointer_cast<const Lighting>(property));
            this->ptrans.push_back(Transform<double, 3>());

            Transform<double, 3> &trans = this->ptrans.back();

            for (const Shape *current = &property->getTarget();
                 nullptr != current;
                 current = current->getParent())
                trans += current->getBasisTransform();
        }
        else
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
}

SamplingLightTracer::~SamplingLightTracer(void) {}

std::list<light_trace_t> SamplingLightTracer::trace(const Point3<double> &point) const
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

    auto sliter = this->sample_lights.begin();
    auto titer = this->ptrans.begin();

    for (double distance; sliter != this->sample_lights.end(); sliter++, titer++)
    {
        Vector3<double> avgv;
        Point3<double> tmp;
        size_t hit = 0;
        const ShapeSampler &sampler = (*sliter)->getTarget().getSampler();
        Intensity<> samplei = (*sliter)->getEmission() / this->samples;
        Intensity<> avgi;

        for (size_t j = 0; this->samples > j; j++)
        {
            tmp = sampler.get();
            tmp.apply(*titer);

            ray.setDirection(point > tmp);

            if (!tracer.trace(this->scene, ray))
            {
                Ray3<double> test = ray;
                test.undo(*titer);
                test.apply((*sliter)->getTarget().getBasisTransform());

                inter = (*sliter)->getTarget().intersect(test);
                Normal3<double> test_n (inter.getNormal());
                test_n.apply(*titer);

                if (-FLT_EPSILON > (test_n & ray.getDirection()))
                {
                    distance = ray.getDirection().length();
                    distance = 1 / (distance * distance);
                    avgv += ray.getDirection() * distance;
                    avgi += samplei * distance;
                    hit++;
                }
            }
        }

        if (hit)
        {
            // avgv /= hit;
            avgv.normalise();
            out.push_back({avgi, avgv});
        }
    }

    return out;
}
