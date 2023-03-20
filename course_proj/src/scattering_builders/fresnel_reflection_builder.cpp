#include "fresnel_reflection_builder.h"

const Attribute &FresnelReflectionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ReflectionBuilder::ATTRIBUTE() \
                            | Attribute(FresnelReflectionBuilder::MAXATTR,
                                        {FresnelReflectionBuilder::ATTRI});
    return attr;
}

FresnelReflectionBuilder::~FresnelReflectionBuilder(void) {}

const Attribute &FresnelReflectionBuilder::getAttribute(void) const
{
    return FresnelReflectionBuilder::ATTRIBUTE();
}

