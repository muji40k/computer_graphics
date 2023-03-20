#include "view_port_renderer.h"

#include "scene_active_projector.h"

#include <iostream>

ViewPortRenderer::~ViewPortRenderer(void) {}

void ViewPortRenderer::render(const Scene &scene,
                              BaseDisplayAdapter &adapter,
                              RenderProgress *const progress)
{
    std::list<std::shared_ptr<const ShapeProperty>> lst = scene.getProperties(SceneActiveProjector::ATTRIBUTE());

    if (0 == lst.size())
        throw CALL_EX(NoActiveProjectorViewPortRenderer);

    const Projector &projector = std::static_pointer_cast<const SceneActiveProjector>(lst.front())->getProjector();
    std::shared_ptr<Projection> projection = projector.project(adapter);

    for (size_t i = 0; adapter.width() > i; i++)
        for (size_t j = 0; adapter.height() > j; j++)
        {
            adapter.setAt(i, j,
                          this->tracer.trace(scene, projection->spawnRay(i, j)));

            if (nullptr != progress)
                progress->step();
        }
}

