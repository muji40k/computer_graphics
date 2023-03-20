#include "difusion_builder.h"

const Attribute &DifusionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringBuilder::ATTRIBUTE() \
                            | Attribute(DifusionBuilder::MAXATTR,
                                        {DifusionBuilder::ATTRI});
    return attr;
}

DifusionBuilder::~DifusionBuilder(void) {}

const Attribute &DifusionBuilder::getAttribute(void) const
{
    return DifusionBuilder::ATTRIBUTE();
}

