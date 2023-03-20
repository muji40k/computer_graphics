#include "complete_renderer.h"

#include "scene_active_projector.h"
#include "projector.h"

CompleteRenderer::CompleteRenderer(const std::shared_ptr<BaseCompleteTracer> &tracer,
                                   const size_t &samples)
    : tracer(tracer)
{
    if (0 == samples)
        throw CALL_EX(NoSamplesCompleteRenderer);

    this->samples = samples;
    this->isamples = (double)1 / this->samples;
    this->spawn_method = &Projection::spawnRay;

    if (1 != samples)
        this->spawn_method = &Projection::sampleRay;
}

CompleteRenderer::~CompleteRenderer(void) {}

void CompleteRenderer::render(const Scene &scene,
                              BaseDisplayAdapter &adapter,
                              RenderProgress *const progress)
{
    std::list<std::shared_ptr<const ShapeProperty>> lst = scene.getProperties(SceneActiveProjector::ATTRIBUTE());

    if (0 == lst.size())
        throw CALL_EX(NoActiveProjectorCompleteRenderer);

    const Projector &projector = std::static_pointer_cast<const SceneActiveProjector>(lst.front())->getProjector();
    std::shared_ptr<Projection> projection = projector.project(adapter);

    for (size_t i = 0; adapter.width() > i; i++)
        for (size_t j = 0; adapter.height() > j; j++)
        {
            Intensity<> avg;

            for (size_t k = 0; this->samples > k; k++)
                avg += this->tracer->trace(scene,
                        (projection.get()->*this->spawn_method)(i, j));

            adapter.setAt(i, j, avg * this->isamples);

            if (nullptr != progress)
                progress->step();
        }
}

