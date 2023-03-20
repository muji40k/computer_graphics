#include "scattering_info.h"

std::shared_ptr<ScatteringProperty> ScatteringInfo::getProperty(const Attribute &attr) const
{
    for (auto item : this->properties)
        if (item->getAttribute() <= attr)
            return item;

    return nullptr;
}

ScatteringInfo &ScatteringInfo::setProperty(const std::shared_ptr<ScatteringProperty> property)
{
    for (auto item : this->properties)
        if (ScatteringProperty::ATTRIBUTE()
            != (item->getAttribute() & property->getAttribute()))
            throw CALL_EX(DuplicateScatteringInfoException);

    this->properties.push_back(property);

    return *this;
}

