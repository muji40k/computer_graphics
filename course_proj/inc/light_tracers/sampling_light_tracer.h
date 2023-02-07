#ifndef _SAMPLING_LIGHT_TRACER_H_
#define _SAMPLING_LIGHT_TRACER_H_

#include <list>
#include <memory>

#include "scene.h"
#include "light_tracer.h"

#include "lighting.h"

class SamplingLightTracer : public LightTracer
{
    public:
        SamplingLightTracer(const Scene &scene, size_t sapmles);
        virtual ~SamplingLightTracer() override;
        virtual std::list<light_trace_t> trace(const Point3<double> &point) override;

    private:
        std::list<std::shared_ptr<const Lighting>> lights;
        std::list<Point3<double>> pcache;

        std::list<std::shared_ptr<const Lighting>> sample_lights;
        std::list<Transform<double, 3>> ptrans;
        size_t samples;

        const Scene &scene;
};

#endif

