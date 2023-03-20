#include "material.h"

void Material::add(const std::shared_ptr<MaterialProperty> &property)
{
    for (auto prop : this->properties)
    {
        if (property == prop)
            throw CALL_EX(DuplicateMateriaclException);
        if (property->getAttribute() <= prop->getAttribute())
            throw CALL_EX(DuplicateTypeMateriaclException);
        if (property->getAttribute() >= prop->getAttribute())
            throw CALL_EX(DuplicateTypeMateriaclException);
    }

    this->properties.push_back(property);
}

void Material::remove(const std::shared_ptr<MaterialProperty> &property)
{
    auto it = this->properties.cbegin();

    for (; it != this->properties.cend() && *it != property; it++);

    if (it == this->properties.cend())
        throw CALL_EX(NothingToRemoveMateriaclException);

    this->properties.erase(it);
}

std::list<std::shared_ptr<MaterialProperty>> Material::get(const Attribute &attr)
{
    std::list<std::shared_ptr<MaterialProperty>> out;

    for (auto prop : this->properties)
        if (prop->getAttribute().contains(attr))
            out.push_back(prop);

    return out;
}

Material::iterator Material::begin(void)
{
    return this->properties.begin();
}

Material::iterator Material::end(void)
{
    return this->properties.end();
}

Material::const_iterator Material::begin(void) const
{
    return this->properties.cbegin();
}

Material::const_iterator Material::end(void) const
{
    return this->properties.cend();
}

Material::const_iterator Material::cbegin(void) const
{
    return this->properties.cbegin();
}

Material::const_iterator Material::cend(void) const
{
    return this->properties.cend();
}

