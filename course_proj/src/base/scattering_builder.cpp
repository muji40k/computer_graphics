#include "scattering_builder.h"

const Attribute &ScatteringBuilder::ATTRIBUTE(void)
{
    static Attribute attr (ScatteringBuilder::MAXATTR,
                           {ScatteringBuilder::ATTRI});
    return attr;
}

ScatteringBuilder::~ScatteringBuilder(void) {}

const Attribute &ScatteringBuilder::getAttribute(void) const
{
    return ScatteringBuilder::ATTRIBUTE();
}

