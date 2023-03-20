#include "transmission_builder.h"

const Attribute &TransmissionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringBuilder::ATTRIBUTE() \
                            | Attribute(TransmissionBuilder::MAXATTR,
                                        {TransmissionBuilder::ATTRI});
    return attr;
}

TransmissionBuilder::~TransmissionBuilder(void) {}

const Attribute &TransmissionBuilder::getAttribute(void) const
{
    return TransmissionBuilder::ATTRIBUTE();
}

