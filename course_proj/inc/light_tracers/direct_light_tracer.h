#ifndef _DIRECT_LIGHT_TRACER_H_
#define _DIRECT_LIGHT_TRACER_H_

#include <list>
#include <memory>

#include "scene.h"
#include "light_tracer.h"

#include "lighting.h"

class DirectLightTracer : public LightTracer
{
    public:
        DirectLightTracer(const Scene &scene);
        virtual ~DirectLightTracer(void) override;
        virtual std::list<light_trace_t> trace(const Point3<double> &point) const override;

    private:
        std::list<std::shared_ptr<const Lighting>> lights;
        std::list<Point3<double>> pcache;
        const Scene &scene;
};

#endif

