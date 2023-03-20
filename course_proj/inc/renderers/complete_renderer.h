#ifndef _COMPLETE_RENDERER_H_
#define _COMPLETE_RENDERER_H_

#include <memory>

#include "renderer.h"
#include "base_complete_tracer.h"
#include "projection.h"

class CompleteRenderer : public Renderer
{
    private:
        using SpawnMethod = Ray3<double> (Projection::*)(size_t, size_t) const;

    public:
        CompleteRenderer(const std::shared_ptr<BaseCompleteTracer> &tracer,
                         const size_t &samples = 1);
        virtual ~CompleteRenderer(void) override;
        virtual void render(const Scene &scene,
                            BaseDisplayAdapter &adapter,
                            RenderProgress *const progress = nullptr) override;

    private:
        std::shared_ptr<BaseCompleteTracer> tracer;
        SpawnMethod spawn_method;
        size_t samples;
        double isamples;
};

DEF_EX(CommonCompleteRendererException, CommonRendererException,
       "General complete renderer exception");
DEF_EX(NoActiveProjectorCompleteRenderer, CommonCompleteRendererException,
       "No active projector in scene");
DEF_EX(NoSamplesCompleteRenderer, CommonCompleteRendererException,
       "Samples amount can't be zero");

#endif

