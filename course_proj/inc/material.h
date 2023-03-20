#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <list>
#include <memory>

#include "base_exception.h"
#include "attribute.h"

#include "material_property.h"

class Material
{
    public:
        using iterator = std::list<std::shared_ptr<MaterialProperty>>::iterator;
        using const_iterator = std::list<std::shared_ptr<MaterialProperty>>::const_iterator;

    public:
        void add(const std::shared_ptr<MaterialProperty> &property);
        void remove(const std::shared_ptr<MaterialProperty> &property);

        std::list<std::shared_ptr<MaterialProperty>> get(const Attribute &attr);

        iterator begin(void);
        iterator end(void);
        const_iterator begin(void)  const;
        const_iterator end(void)    const;
        const_iterator cbegin(void) const;
        const_iterator cend(void)   const;

    private:
        std::list<std::shared_ptr<MaterialProperty>> properties;
};

DEF_EX(CommonMaterialException, BaseException, "General material exception");
DEF_EX(DuplicateMateriaclException, CommonMaterialException,
       "Property duplicate material exception");
DEF_EX(DuplicateTypeMateriaclException, CommonMaterialException,
       "Property type duplicate material exception");
DEF_EX(NothingToRemoveMateriaclException, CommonMaterialException,
       "No such property to delete material exception");

#endif

