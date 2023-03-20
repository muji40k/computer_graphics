#include "scattering_base_function.h"

const Attribute &ScatteringBaseFunction::ATTRIBUTE(void)
{
    static Attribute attr = ScatteringProperty::ATTRIBUTE() \
                            | Attribute(ScatteringBaseFunction::MAXATTR,
                                        {ScatteringBaseFunction::ATTRI});
    return attr;
}

ScatteringBaseFunction::ScatteringBaseFunction(const std::shared_ptr<ScatteringFunction> &function)
    : function(function) {}

ScatteringBaseFunction::~ScatteringBaseFunction(void) {}

const std::shared_ptr<ScatteringFunction> &ScatteringBaseFunction::getBaseFunction(void)
{
    return this->function;
}

const Attribute &ScatteringBaseFunction::getAttribute(void) const
{
    return ScatteringBaseFunction::ATTRIBUTE();
}

