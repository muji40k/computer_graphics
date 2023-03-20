#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <mutex>

#include "scene.h"
#include "base_display_adapter.h"

#include "base_exception.h"

class RenderProgress
{
    public:
        RenderProgress(const BaseDisplayAdapter &adapter);
        void clear(void);
        double progress(void) const;
        void step(void);

    private:
        std::mutex mutex;
        size_t current;
        size_t max;
};

class Renderer
{
    public:
        virtual ~Renderer(void) = 0;
        virtual void render(const Scene &scene,
                            BaseDisplayAdapter &adapter,
                            RenderProgress *const progress = nullptr) = 0;
};

DEF_EX(CommonRendererException, BaseException, "General Renderer exception");

#endif

