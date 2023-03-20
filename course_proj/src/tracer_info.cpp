#include "tracer_info.h"

std::shared_ptr<TracerProperty> TracerInfo::getProperty(const Attribute &attr) const
{
    for (auto item : this->properties)
        if (item->getAttribute() <= attr)
            return item;

    return nullptr;
}

TracerInfo &TracerInfo::setProperty(const std::shared_ptr<TracerProperty> property)
{
    for (auto item : this->properties)
        if (TracerProperty::ATTRIBUTE()
            != (item->getAttribute() & property->getAttribute()))
            throw CALL_EX(DuplicateTracerInfoException);

    this->properties.push_back(property);

    return *this;
}

