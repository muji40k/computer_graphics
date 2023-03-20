#include "scene_active_projector.h"

SceneActiveProjector::SceneActiveProjector(const std::shared_ptr<const Projector> &projector)
    : projector(projector) {}

SceneActiveProjector::~SceneActiveProjector(void) {}

const Projector &SceneActiveProjector::getProjector(void) const
{
    return *this->projector;
}

void SceneActiveProjector::setProjector(const std::shared_ptr<const Projector> &projector)
{
    this->projector = projector;
}

const Attribute &SceneActiveProjector::ATTRIBUTE(void)
{
    static const Attribute attr = CommonProperty::ATTRIBUTE() \
                                  | Attribute(SceneActiveProjector::MAXATTR,
                                              {SceneActiveProjector::ATTRI});
    return attr;
}

const Attribute &SceneActiveProjector::getAttribute(void) const
{
    return SceneActiveProjector::ATTRIBUTE();
}

