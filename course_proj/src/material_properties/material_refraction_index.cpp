#include "material_refraction_index.h"

const Attribute &MaterialRefractionIndex::ATTRIBUTE(void)
{
    static Attribute attr = MaterialProperty::ATTRIBUTE() \
                            | Attribute(MaterialRefractionIndex::MAXATTR,
                                        {MaterialRefractionIndex::ATTRI});
    return attr;
}

MaterialRefractionIndex::MaterialRefractionIndex(const std::complex<double> &n,
                                                 const Intensity<> &albedo)
    : n(std::make_shared<std::complex<double>>(n)),
      albedo(std::make_shared<Intensity<>>(albedo)) {}

MaterialRefractionIndex::~MaterialRefractionIndex(void) {}

const Attribute &MaterialRefractionIndex::getAttribute(void) const
{
    return MaterialRefractionIndex::ATTRIBUTE();
}

const std::complex<double> &MaterialRefractionIndex::getValue(void)
{
    return *this->n;
}

const Intensity<> &MaterialRefractionIndex::getAlbedo(void)
{
    return *this->albedo;
}

