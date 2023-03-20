#include "specular_reflection_builder.h"

#include "specular_reflection_function.h"
#include "scattering_scale.h"

const Attribute &SpecularReflectionBuilder::ATTRIBUTE(void)
{
    static Attribute attr = ReflectionBuilder::ATTRIBUTE() \
                            | Attribute(SpecularReflectionBuilder::MAXATTR,
                                        {SpecularReflectionBuilder::ATTRI});
    return attr;
}

SpecularReflectionBuilder::~SpecularReflectionBuilder(void) {}

const Attribute &SpecularReflectionBuilder::getAttribute(void) const
{
    return SpecularReflectionBuilder::ATTRIBUTE();
}

std::shared_ptr<ScatteringFunction> SpecularReflectionBuilder::build(const ScatteringInfo &info) const
{
    std::shared_ptr<ScatteringScale> scale = \
        std::static_pointer_cast<ScatteringScale>(info.getProperty(ScatteringScale::ATTRIBUTE()));

    if (nullptr == scale)
        throw CALL_EX_MSG(NoReqiredPropertyScatteringBuilderException,
                          NO_REQIRED_MSG(ScatteringScale));

    return std::make_shared<SpecularReflectionFunction>(scale->getScale());
}

