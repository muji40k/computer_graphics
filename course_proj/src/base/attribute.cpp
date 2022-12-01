#include "attribute.h"

Attribute::Attribute(const size_t amount)
{
    this->amount = amount;
    this->real = amount / MAX_ASIZE;

    if (0 != amount % MAX_ASIZE)
        this->real += 1;

    this->allocate(this->real);
}

Attribute::Attribute(const size_t amount, std::initializer_list<size_t> indexes)
    : Attribute(amount)
{
    for (size_t index : indexes)
        this->set(index);
}

Attribute::Attribute(const Attribute &attr)
{
    this->amount = attr.amount;
    this->real = attr.real;
    this->allocate(this->real);

    for (size_t i = 0; this->real > i; i++)
        this->arr[i] = attr.arr[i];
}

Attribute::Attribute(Attribute &&attr)
{
    this->amount = attr.amount;
    this->real = attr.real;
    this->arr.reset(attr.arr.release());
}

Attribute &Attribute::operator = (const Attribute &another)
{
    this->amount = another.amount;
    this->real = another.real;
    this->allocate(this->real);

    for (size_t i = 0; this->real > i; i++)
        this->arr[i] = another.arr[i];

    return *this;
}

Attribute &Attribute::operator = (Attribute &&another)
{
    this->amount = another.amount;
    this->real = another.real;
    this->arr.reset(another.arr.release());

    return *this;
}

bool Attribute::operator == (const Attribute &another) const
{
    this->isCompatible(another);

    for (size_t i = 0; this->real > i; i++)
        if (this->arr[i] != another.arr[i])
            return false;

    return true;
}

bool Attribute::operator != (const Attribute &another) const
{
    return !((*this) == another);
}

bool Attribute::operator > (const Attribute &another) const
{
    return another < *this;
}

bool Attribute::operator < (const Attribute &another) const
{
    this->isCompatible(another);

    if (*this == another)
        return false;

    for (size_t i = 0; this->real > i; i++)
        if (this->arr[i] & (~another.arr[i]))
            return false;

    return true;
}

bool Attribute::operator >= (const Attribute &another) const
{
    return another <= *this;
}

bool Attribute::operator <= (const Attribute &another) const
{
    this->isCompatible(another);

    for (size_t i = 0; this->real > i; i++)
        if (this->arr[i] & (~another.arr[i]))
            return false;

    return true;
}

Attribute Attribute::operator & (const Attribute &another) const
{
    this->isCompatible(another);
    Attribute out (*this);

    return out &= another;
}

Attribute Attribute::operator | (const Attribute &another) const
{
    this->isCompatible(another);
    Attribute out (*this);

    return out |= another;
}

Attribute Attribute::operator ^ (const Attribute &another) const
{
    this->isCompatible(another);
    Attribute out (*this);

    return out ^= another;
}

Attribute Attribute::operator ~ (void) const
{
    Attribute out (*this);

    for (size_t i = 0; this->real > i; i++)
        out.arr[i] = ~out.arr[i];

    AType num = ~0;

    for (size_t i = 0; (this->amount - (this->real - 1) * MAX_ASIZE) > i; i++)
        num >>= 1;

    out.arr[this->real - 1] ^= num;

    return out;
}

Attribute &Attribute::operator &= (const Attribute &another)
{
    this->isCompatible(another);

    for (size_t i = 0; this->real > i; i++)
        this->arr[i] &= another.arr[i];

    return *this;
}

Attribute &Attribute::operator |= (const Attribute &another)
{
    this->isCompatible(another);

    for (size_t i = 0; this->real > i; i++)
        this->arr[i] |= another.arr[i];

    return *this;
}

Attribute &Attribute::operator ^= (const Attribute &another)
{
    this->isCompatible(another);

    for (size_t i = 0; this->real > i; i++)
        this->arr[i] ^= another.arr[i];

    return *this;
}

bool Attribute::contains(const Attribute &another) const
{
    return another < *this;
}

void Attribute::set(const size_t index) const
{
    this->checkIndex(index);

    size_t i = index / MAX_ASIZE;
    size_t j = index % MAX_ASIZE;
    this->arr[i] |= (1 << (MAX_ASIZE - j - 1));
}

void Attribute::reset(const size_t index) const
{
    this->checkIndex(index);

    size_t i = index / MAX_ASIZE;
    size_t j = index % MAX_ASIZE;
    this->arr[i] &= (~(1 << (MAX_ASIZE - j - 1)));
}

bool Attribute::get(const size_t index) const
{
    this->checkIndex(index);

    size_t i = index / MAX_ASIZE;
    size_t j = index % MAX_ASIZE;

    return this->arr[i] & (1 << (MAX_ASIZE - j - 1));
}

bool Attribute::operator () (const size_t index) const
{
    return this->get(index);
}

void Attribute::allocate(const size_t amount)
{
    if (0 == amount)
        throw CALL_EX(ErrorAttributeALlocationEmptyException);

    try
    {
        this->arr.reset(new AType[amount]);

        for (size_t i = 0; amount > i; this->arr[i++] = 0);
    }
    catch (std::bad_alloc &)
    {
        throw CALL_EX(ErrorAttributeAllocationException);
    }
}

void Attribute::isCompatible(const Attribute &another) const
{
    if (this->amount != another.amount)
        throw CALL_EX(ErrorAttributeIncompatibleException);
}

void Attribute::checkIndex(const size_t index) const
{
    if (this->amount <= index)
        throw CALL_EX(ErrorAttributeIndexViolationException);
}

