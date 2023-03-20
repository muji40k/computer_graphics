#include "lighting.h"

Lighting::Lighting(Shape *target, const Intensity<> &emission)
    : DedicatedProperty(target)
{
    this->emission = emission;
}

Lighting::~Lighting(void) {}

const Intensity<> &Lighting::getEmission(void) const { return this->emission; }

void Lighting::setEmission(const Intensity<> &emission)
{
    this->emission = emission;
}

const Attribute &Lighting::ATTRIBUTE(void)
{
    static const Attribute attr = DedicatedProperty::ATTRIBUTE() \
                                  | Attribute(Lighting::MAXATTR,
                                              {Lighting::ATTRI});
    return attr;
}

const Attribute &Lighting::getAttribute(void) const
{
    return Lighting::ATTRIBUTE();
}

