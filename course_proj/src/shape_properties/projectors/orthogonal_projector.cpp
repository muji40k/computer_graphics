#include "orthogonal_projector.h"
#include "orthogonal_projection.h"

OrthogonalProjector::OrthogonalProjector(Shape *target) : Projector(target) {}

OrthogonalProjector::~OrthogonalProjector(void) {}

std::shared_ptr<Projection> OrthogonalProjector::project(const BaseDisplayAdapter &display) const
{
    return std::shared_ptr<Projection>(new OrthogonalProjection(display, this->getTarget()));
}

const Attribute &OrthogonalProjector::ATTRIBUTE(void)
{
    static const Attribute attr = Projector::ATTRIBUTE() \
                                  | Attribute(OrthogonalProjector::MAXATTR,
                                              {OrthogonalProjector::ATTRI});
    return attr;
}

const Attribute &OrthogonalProjector::getAttribute(void) const
{
    return OrthogonalProjector::ATTRIBUTE();
}

