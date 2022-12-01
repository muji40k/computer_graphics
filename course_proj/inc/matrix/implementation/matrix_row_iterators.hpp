#ifndef _MATRIX_ROW_ITERATORS_HPP_
#define _MATRIX_ROW_ITERATORS_HPP_

#include "matrix_row_iterators.h"
#include "matrix_row_iterators_exceptions.h"

template <typename Type>
MatrixRowIterator<Type>::MatrixRowIterator(MatrixRow<Type> &row)
{
    this->ptr = row.data;
    this->index = MIN_INDEX;
    this->size = row.size + MIN_INDEX;
}

template <typename Type>
MatrixRowIterator<Type>::MatrixRowIterator(const MatrixRowIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixRowIterator<Type>::MatrixRowIterator(MatrixRowIterator<Type> &&iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator = (const MatrixRowIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index= iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator = (MatrixRow<Type> &row)
{
    this->ptr = row.data;
    this->index = MIN_INDEX;
    this->size = row.size + MIN_INDEX;
}

template <typename Type>
MatrixRowIterator<Type>::operator bool(void) const
{
    return nullptr != (this->ptr).lock();
}

template <typename Type>
bool MatrixRowIterator<Type>::isExpired(void) const
{
    return (this->ptr).expired();
}

template <typename Type>
Type &MatrixRowIterator<Type>::operator * (void)
{
    return this->get();
}

template <typename Type>
Type &MatrixRowIterator<Type>::get(void)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (this->size == this->index|| MIN_INDEX - 1 == this->index)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    return (this->ptr).lock()[this->index - MIN_INDEX];
}

template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator ++ (void)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == this->size)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index++;

    return *this;
}

template <typename Type>
MatrixRowIterator<Type> MatrixRowIterator<Type>::operator ++ (int)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == this->size)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    MatrixRowIterator<Type> tmp(*this);
    this->index++;

    return tmp;
}

template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator -- (void)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (MIN_INDEX - 1 == this->index)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index--;

    return *this;
}

template <typename Type>
MatrixRowIterator<Type> MatrixRowIterator<Type>::operator -- (int)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (MIN_INDEX - 1 == this->index)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    MatrixRowIterator<Type> tmp(*this);
    this->index--;

    return tmp;
}

template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator += (const size_t offset)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (this->index + offset > this->size)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index += offset;

    return *this;
}

template <typename Type>
MatrixRowIterator<Type> MatrixRowIterator<Type>::operator + (const size_t offset)
                        const
{
    MatrixRowIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
MatrixRowIterator<Type> MatrixRowIterator<Type>::operator - (const size_t offset)
                        const
{
    MatrixRowIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}


template <typename Type>
MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator -= (const size_t offset)
{
    if (!(*this))
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (offset + MIN_INDEX - 1 > this->index)
        throw ErrorMatrixRowIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index -= offset;

    return *this;
}

template <typename Type>
int MatrixRowIterator<Type>::compare(const MatrixRowIterator<Type> &iter) const
{
    if (!(*this) || !iter)
        throw ErrorMatrixRowIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired() || iter.isExpired())
        throw ErrorMatrixRowIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == iter.index)
        return 0;

    if (this->index > iter.index)
        return 1;

    return -1;
}

template <typename Type>
bool MatrixRowIterator<Type>::operator == (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 == this->compare(iter);
}

template <typename Type>
bool MatrixRowIterator<Type>::operator != (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 != this->compare(iter);
}

template <typename Type>
bool MatrixRowIterator<Type>::operator >= (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 <= this->compare(iter);
}

template <typename Type>
bool MatrixRowIterator<Type>::operator <= (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 >= this->compare(iter);
}

template <typename Type>
bool MatrixRowIterator<Type>::operator > (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 < this->compare(iter);
}

template <typename Type>
bool MatrixRowIterator<Type>::operator < (const MatrixRowIterator<Type> &iter)
     const
{
    return 0 > this->compare(iter);
}

template <typename Type>
void MatrixRowIterator<Type>::set_ptr(const std::weak_ptr<Type[]> &ptr)
{
    this->ptr = ptr;
}

template <typename Type>
void MatrixRowIterator<Type>::set_index(const size_t index)
{
    this->index = index + MIN_INDEX;
}

template <typename Type>
void MatrixRowIterator<Type>::set_size(const size_t size)
{
    this->size = size + MIN_INDEX;
}

template <typename Type>
void MatrixRowIterator<Type>::set_iter(const MatrixRowIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
ConstMatrixRowIterator<Type>::ConstMatrixRowIterator(const MatrixRow<Type> &row)
: MatrixRowIterator<Type>::MatrixRowIterator()
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
ConstMatrixRowIterator<Type>::ConstMatrixRowIterator(const ConstMatrixRowIterator<Type> &iter)
: MatrixRowIterator<Type>::MatrixRowIterator(iter) {}

template <typename Type>
ConstMatrixRowIterator<Type>::ConstMatrixRowIterator(ConstMatrixRowIterator<Type> &&iter)
: MatrixRowIterator<Type>::MatrixRowIterator(iter) {}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator = (const ConstMatrixRowIterator<Type> &iter)
{
    this->MatrixRowIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator = (const MatrixRow<Type> &row)
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
const Type &ConstMatrixRowIterator<Type>::operator * (void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
const Type &ConstMatrixRowIterator<Type>::get(void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator ++ (void)
{
    this->MatrixRowIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ConstMatrixRowIterator<Type> ConstMatrixRowIterator<Type>::operator ++ (int)
{
    ConstMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator -- (void)
{
    this->MatrixRowIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ConstMatrixRowIterator<Type> ConstMatrixRowIterator<Type>::operator -- (int)
{
    ConstMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator += (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ConstMatrixRowIterator<Type> ConstMatrixRowIterator<Type>::operator + (const size_t offset) const
{
    ConstMatrixRowIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ConstMatrixRowIterator<Type> ConstMatrixRowIterator<Type>::operator - (const size_t offset) const
{
    ConstMatrixRowIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

template <typename Type>
ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(MatrixRow<Type> &row)
: MatrixRowIterator<Type>::MatrixRowIterator()
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_index(row.size - 1);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(const ReverseMatrixRowIterator<Type> &iter)
: MatrixRowIterator<Type>::MatrixRowIterator(iter) {}

template <typename Type>
ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(ReverseMatrixRowIterator<Type> &&iter)
: MatrixRowIterator<Type>::MatrixRowIterator(iter) {}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator = (const ReverseMatrixRowIterator<Type> &iter)
{
    this->MatrixRowIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator = (MatrixRow<Type> &row)
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_index(row.size - 1);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
Type &ReverseMatrixRowIterator<Type>::operator * (void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
Type &ReverseMatrixRowIterator<Type>::get(void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator ++ (void)
{
    this->MatrixRowIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ReverseMatrixRowIterator<Type> ReverseMatrixRowIterator<Type>::operator ++ (int)
{
    ReverseMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator -- (void)
{
    this->MatrixRowIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ReverseMatrixRowIterator<Type> ReverseMatrixRowIterator<Type>::operator -- (int)
{
    ReverseMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator += (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ReverseMatrixRowIterator<Type> ReverseMatrixRowIterator<Type>::operator + (const size_t offset) const
{
    ReverseMatrixRowIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ReverseMatrixRowIterator<Type> ReverseMatrixRowIterator<Type>::operator - (const size_t offset) const
{
    ReverseMatrixRowIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

template <typename Type>
bool ReverseMatrixRowIterator<Type>::operator >= (const ReverseMatrixRowIterator<Type> &iter) const
{
    return this->MatrixRowIterator<Type>::operator <= (iter);
}

template <typename Type>
bool ReverseMatrixRowIterator<Type>::operator <= (const ReverseMatrixRowIterator<Type> &iter) const
{
    return this->MatrixRowIterator<Type>::operator >= (iter);
}

template <typename Type>
bool ReverseMatrixRowIterator<Type>::operator > (const ReverseMatrixRowIterator<Type> &iter) const
{
    return this->MatrixRowIterator<Type>::operator < (iter);
}

template <typename Type>
bool ReverseMatrixRowIterator<Type>::operator < (const ReverseMatrixRowIterator<Type> &iter) const
{
    return this->MatrixRowIterator<Type>::operator > (iter);
}

template <typename Type>
ConstReverseMatrixRowIterator<Type>::ConstReverseMatrixRowIterator(const MatrixRow<Type> &row)
: ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator()
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_index(row.size - 1);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
ConstReverseMatrixRowIterator<Type>::ConstReverseMatrixRowIterator(const ConstReverseMatrixRowIterator<Type> &iter)
: ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(iter) {}

template <typename Type>
ConstReverseMatrixRowIterator<Type>::ConstReverseMatrixRowIterator(ConstReverseMatrixRowIterator<Type> &&iter)
: ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(iter) {}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator = (const ConstReverseMatrixRowIterator<Type> &iter)
{
    this->MatrixRowIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator = (const MatrixRow<Type> &row)
{
    std::weak_ptr<Type[]> ptr = row.data;
    this->MatrixRowIterator<Type>::set_ptr(ptr);
    this->MatrixRowIterator<Type>::set_index(row.size - 1);
    this->MatrixRowIterator<Type>::set_size(row.size);
}

template <typename Type>
const Type &ConstReverseMatrixRowIterator<Type>::operator * (void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
const Type &ConstReverseMatrixRowIterator<Type>::get(void)
{
    return this->MatrixRowIterator<Type>::get();
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator ++ (void)
{
    this->MatrixRowIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> ConstReverseMatrixRowIterator<Type>::operator ++ (int)
{
    ConstReverseMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator -- (void)
{
    this->MatrixRowIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> ConstReverseMatrixRowIterator<Type>::operator -- (int)
{
    ConstReverseMatrixRowIterator<Type> tmp(*this);
    this->MatrixRowIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator += (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixRowIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> ConstReverseMatrixRowIterator<Type>::operator + (const size_t offset) const
{
    ConstReverseMatrixRowIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> ConstReverseMatrixRowIterator<Type>::operator - (const size_t offset) const
{
    ConstReverseMatrixRowIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

#endif

