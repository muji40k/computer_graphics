#include "specular_transmission_builder.h"

#include "specular_transmission_function.h"
#include "scattering_scale.h"

const Attribute &SpecularTransmissionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = TransmissionBuilder::ATTRIBUTE() \
                            | Attribute(SpecularTransmissionBuilder::MAXATTR,
                                        {SpecularTransmissionBuilder::ATTRI});
    return attr;
}

SpecularTransmissionBuilder::~SpecularTransmissionBuilder(void) {}

const Attribute &SpecularTransmissionBuilder::getAttribute(void) const
{
    return SpecularTransmissionBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> SpecularTransmissionBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));

    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    return std::make_shared<SpecularTransmissionFunction>(scale->getScale());
}

