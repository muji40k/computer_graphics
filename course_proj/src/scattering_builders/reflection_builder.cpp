#include "reflection_builder.h"

const Attribute &ReflectionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringBuilder::ATTRIBUTE() \
                            | Attribute(ReflectionBuilder::MAXATTR,
                                        {ReflectionBuilder::ATTRI});
    return attr;
}

ReflectionBuilder::~ReflectionBuilder(void) {}

const Attribute &ReflectionBuilder::getAttribute(void) const
{
    return ReflectionBuilder::ATTRIBUTE();
}

