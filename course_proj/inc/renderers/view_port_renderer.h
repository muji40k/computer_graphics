#ifndef _VIEW_PORT_RENDERER_H_
#define _VIEW_PORT_RENDERER_H_

#include "renderer.h"
#include "view_port_tracer.h"

class ViewPortRenderer : public Renderer
{
    public:
        virtual ~ViewPortRenderer(void) override;
        virtual void render(const Scene &scene,
                            BaseDisplayAdapter &adapter,
                            RenderProgress *const progress = nullptr) override;

    private:
        ViewPortTracer tracer;
};

DEF_EX(CommonViewPortRendererException, CommonRendererException,
       "General viewport renderer exception");
DEF_EX(NoActiveProjectorViewPortRenderer, CommonViewPortRendererException,
       "No active projector in scene");

#endif

