#include "lambert_difusion_builder.h"

#include "lambert_difusion_function.h"
#include "scattering_scale.h"

const Attribute &LambertDifusionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = DifusionBuilder::ATTRIBUTE() \
                            | Attribute(LambertDifusionBuilder::MAXATTR,
                                        {LambertDifusionBuilder::ATTRI});
    return attr;
}

LambertDifusionBuilder::~LambertDifusionBuilder(void) {}

const Attribute &LambertDifusionBuilder::getAttribute(void) const
{
    return LambertDifusionBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> LambertDifusionBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));

    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    return std::make_shared<LambertDifusionFunction>(scale->getScale());
}

