#include "ambient_lighting.h"

AmbientLighting::AmbientLighting(const Intensity<> emission)
{
    this->emission = emission;
}

AmbientLighting::~AmbientLighting(void) {}

const Intensity<> &AmbientLighting::getEmission(void) const { return this->emission; }

void AmbientLighting::setEmission(const Intensity<> emission)
{
    this->emission = emission;
}

const Attribute &AmbientLighting::ATTRIBUTE(void)
{
    static const Attribute attr = CommonProperty::ATTRIBUTE() \
                                  | Attribute(AmbientLighting::MAXATTR,
                                              {AmbientLighting::ATTRI});
    return attr;
}

const Attribute &AmbientLighting::getAttribute(void) const
{
    return AmbientLighting::ATTRIBUTE();
}

