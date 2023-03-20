#ifndef _PARALLEL_RENDER_DECORATOR_H_
#define _PARALLEL_RENDER_DECORATOR_H_

#include <memory>
#include <pthread.h>
#include <mutex>

#include "renderer.h"

#include "base_exception.h"

class ParallelRendererDecorator : public Renderer
{
    public:
        ParallelRendererDecorator(Renderer &renderer,
                                  size_t bucketw_amount, size_t bucketh_amount,
                                  size_t thread_amount);
        virtual ~ParallelRendererDecorator(void) override;
        virtual void render(const Scene &scene,
                            BaseDisplayAdapter &adapter,
                            RenderProgress *const progress = nullptr) override;

    private:
        Renderer &renderer;
        size_t width;
        size_t height;
        size_t threads;
};

DEF_EX(CommonParallelRendererException, CommonRendererException,
       "General ParallelRenderer exception");
DEF_EX(NotEnoughtThreadParallelRendererException, CommonParallelRendererException,
       "Renderer must have at least 2 threads");
DEF_EX(ThreadParallelRendererException, CommonParallelRendererException,
       "Unable to create thread");

#endif

