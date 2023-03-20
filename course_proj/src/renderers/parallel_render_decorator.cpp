#include "parallel_render_decorator.h"

#include <list>

#include "matrix.h"

#include "split_display_decorator.h"

typedef struct
{
    pthread_t thread;
    const Scene *scene;
    Renderer *renderer;
    BaseDisplayAdapter *decorator;
    RenderProgress *progress;
    bool active;
} thread_arg_t;


static void *render_func(void *_arg);

ParallelRendererDecorator::ParallelRendererDecorator(Renderer &renderer,
                                                     size_t bucketw,
                                                     size_t bucketh,
                                                     size_t threada)
    : renderer(renderer), width(bucketw), height(bucketh), threads(threada)
{
    if (2 >= threada)
        throw CALL_EX(NotEnoughtThreadParallelRendererException);
}

ParallelRendererDecorator::~ParallelRendererDecorator(void) {}

void ParallelRendererDecorator::render(const Scene &scene,
                                       BaseDisplayAdapter &adapter,
                                       RenderProgress *const progress)
{
    std::unique_ptr<thread_arg_t[]> args = std::make_unique<thread_arg_t[]>(this->threads);
    std::list<SplitDisplayDecorator> splits;

    for (size_t i = 0; this->threads > i; i++)
    {
        args[i].scene = &scene;
        args[i].renderer = &this->renderer;
        args[i].progress = progress;
        args[i].active = false;
    }

    size_t lx = adapter.width(), ly = adapter.height();
    size_t stepx = lx / this->width;
    size_t stepy = ly / this->height;
    size_t lastx = lx - stepx * (this->width - 1);
    size_t lasty = ly - stepy * (this->height - 1);
    size_t cstepx = stepx, cstepy = stepy;
    size_t act = 0;
    int rc = EXIT_SUCCESS;

    for (size_t i = 0; EXIT_SUCCESS == rc && this->width > i; i++)
    {
        if (this->threads == i + 1)
            cstepx = lastx;

        for (size_t j = 0; EXIT_SUCCESS == rc && this->height > j; j++)
        {
            for (; args[act].active; act = (act + 1) % this->threads);

            if (this->threads == j + 1)
                cstepy = lasty;

            splits.push_back(SplitDisplayDecorator(adapter,
                                                   i * stepx, j * stepy,
                                                   cstepx, cstepy));
            args[act].decorator = &splits.back();
            args[act].active = true;

            rc = pthread_create(&args[act].thread, NULL, render_func,
                                &args[act]);
        }

        cstepy = stepy;
    }

    if (EXIT_SUCCESS == rc)
        for (size_t i = 0; this->threads > i; i++)
            pthread_join(args[i].thread, NULL);
    else
    {
        for (size_t i = 0; this->threads > i; i++)
            if (args[i].active)
                pthread_cancel(args[i].thread);

        throw CALL_EX(ThreadParallelRendererException);
    }
}

static void *render_func(void *_arg)
{
    thread_arg_t *arg = (thread_arg_t *)_arg;

    arg->renderer->render(*arg->scene, *arg->decorator, arg->progress);
    arg->active = false;

    return _arg;
}

