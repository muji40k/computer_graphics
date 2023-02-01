#include "pinhole_projector.h"
#include "pinhole_projection.h"

PinholeProjector::PinholeProjector(Shape *target, const double pin_offset)
    : Projector(target)
{
    if (0 > pin_offset)
        throw CALL_EX(NegativeOffsetPProjectionException);

    this->f = pin_offset;
}

PinholeProjector::~PinholeProjector(void) {}

std::shared_ptr<Projection> PinholeProjector::project(const BaseDisplayAdapter &display) const
{
    return std::shared_ptr<Projection>(new PinholeProjection(display,
                                                             this->getTarget(),
                                                             this->f));
}

double PinholeProjector::getPinOffset(void)
{
    return this->f;
}

void PinholeProjector::setPinOffset(const double offset)
{
    if (0 > offset)
        throw CALL_EX(NegativeOffsetPProjectionException);

    this->f = offset;
}

const Attribute &PinholeProjector::ATTRIBUTE(void)
{
    static const Attribute attr = Projector::ATTRIBUTE() \
                                  | Attribute(PinholeProjector::MAXATTR,
                                              {PinholeProjector::ATTRI});
    return attr;
}

const Attribute &PinholeProjector::getAttribute(void) const
{
    return PinholeProjector::ATTRIBUTE();
}

