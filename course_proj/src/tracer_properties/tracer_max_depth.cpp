#include "tracer_max_depth.h"

const Attribute &TracerMaxDepth::ATTRIBUTE(void)
{
    static Attribute attr = TracerProperty::ATTRIBUTE() \
                            | Attribute(TracerMaxDepth::MAXATTR,
                                        {TracerMaxDepth::ATTRI});
    return attr;
}

TracerMaxDepth::TracerMaxDepth(const size_t depth)
{
    this->depth = depth;
}

TracerMaxDepth::~TracerMaxDepth(void) {}

const Attribute &TracerMaxDepth::getAttribute(void) const
{
    return TracerMaxDepth::ATTRIBUTE();
}

size_t TracerMaxDepth::getValue(void) const
{
    return this->depth;
}

