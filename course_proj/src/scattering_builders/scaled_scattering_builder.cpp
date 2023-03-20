#include "scaled_scattering_builder.h"

#include "scaled_scattering_function.h"
#include "scattering_base_function.h"
#include "scattering_scale.h"

const Attribute &ScaledScatteringBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringBuilder::ATTRIBUTE() \
                            | Attribute(ScatteringBuilder::MAXATTR,
                                        {ScatteringBuilder::ATTRI});
    return attr;
}

ScaledScatteringBuilder::~ScaledScatteringBuilder(void) {}

std::shared_ptr<ScatteringFunction> ScaledScatteringBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringBaseFunction> base_func = \
        std::static_pointer_cast<ScatteringBaseFunction>(info.getProperty(ScatteringBaseFunction::ATTRIBUTE()));
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));

    if (nullptr == base_func)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringBaseFunction));

    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    return std::make_shared<ScaledScatteringFunction>(base_func->getBaseFunction(),
                                                      scale->getScale());
}

const Attribute &ScaledScatteringBuilder::getAttribute(void) const
{
    return ScaledScatteringBuilder::ATTRIBUTE();
}

