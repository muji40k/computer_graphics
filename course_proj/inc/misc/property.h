#ifndef _PROPERTY_H_
#define _PROPERTY_H_

template <typename ClassType, typename Type>
class Property
{
    public:
        using SetMethod = void (ClassType::*)(const Type &);
        using GetMethod = const Type &(ClassType::*)(void) const;

        Property(void) = default;
        Property(ClassType *owner, SetMethod setter, GetMethod getter);
        void init(ClassType *owner, SetMethod setter, GetMethod getter);

        operator const Type &(void) const;
        const Type &operator = (const Type &value) const;
        const Type &operator = (const Property<ClassType, Type> &value) const;

        Property(const Property&) = delete;
        // Property& operator=(const Property&) = delete;

    private:
        ClassType *owner = nullptr;
        SetMethod setter = nullptr;
        GetMethod getter = nullptr;
};

template <typename ClassType, typename Type>
Property<ClassType, Type>::Property(ClassType *owner,
                                    SetMethod setter, GetMethod getter)
    : owner(owner), setter(setter), getter(getter) {}

template <typename ClassType, typename Type>
void Property<ClassType, Type>::init(ClassType *owner,
                                     SetMethod setter, GetMethod getter)
{
    this->owner = owner;
    this->setter = setter;
    this->getter = getter;
}

template <typename ClassType, typename Type>
Property<ClassType, Type>::operator const Type &(void) const
{
    return ((this->owner)->*(this->getter))();
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator = (const Type &value) const
{
    ((this->owner)->*(this->setter))(value);

    return ((this->owner)->*(this->getter))();
}

template <typename ClassType, typename Type>
const Type &Property<ClassType, Type>::operator = (const Property<ClassType, Type> &value) const
{
    ((this->owner)->*(this->setter))(((value.owner)->*(value.getter))());

    return ((this->owner)->*(this->getter))();
}

#endif

