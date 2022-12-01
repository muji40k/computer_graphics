#ifndef _MATRIX_ITERATORS_HPP_
#define _MATRIX_ITERATORS_HPP_

#include "matrix_iterators.h"
#include "matrix_iterators_exceptions.h"

template <typename Type>
MatrixIterator<Type>::MatrixIterator(Matrix<Type> &matrix)
{
    this->ptr = matrix.data;
    this->index = MIN_INDEX;
    this->size = matrix.size + MIN_INDEX;
}

template <typename Type>
MatrixIterator<Type>::MatrixIterator(const MatrixIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixIterator<Type>::MatrixIterator(MatrixIterator<Type> &&iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator = (const MatrixIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index= iter.index;
    this->size = iter.size;
}

template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator = (Matrix<Type> &matrix)
{
    this->ptr = matrix.data;
    this->index = MIN_INDEX;
    this->size = matrix.size + MIN_INDEX;
}

template <typename Type>
MatrixIterator<Type>::operator bool(void) const
{
    return nullptr != (this->ptr).lock();
}

template <typename Type>
bool MatrixIterator<Type>::isExpired(void) const
{
    return (this->ptr).expired();
}

template <typename Type>
MatrixRow<Type> &MatrixIterator<Type>::operator * (void)
{
    return this->get();
}

template <typename Type>
MatrixRow<Type> &MatrixIterator<Type>::get(void)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (this->size == this->index|| MIN_INDEX - 1 == this->index)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    return (this->ptr).lock()[this->index - MIN_INDEX];
}

template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator ++ (void)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == this->size)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index++;

    return *this;
}

template <typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator ++ (int)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == this->size)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    MatrixIterator<Type> tmp(*this);
    this->index++;

    return tmp;
}

template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator -- (void)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (MIN_INDEX - 1 == this->index)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index--;

    return *this;
}

template <typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator -- (int)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (MIN_INDEX - 1 == this->index)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    MatrixIterator<Type> tmp(*this);
    this->index--;

    return tmp;
}

template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator += (const size_t offset)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (this->index + offset > this->size)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index += offset;

    return *this;
}

template <typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator + (const size_t offset)
                        const
{
    MatrixIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator - (const size_t offset)
                        const
{
    MatrixIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}


template <typename Type>
MatrixIterator<Type> &MatrixIterator<Type>::operator -= (const size_t offset)
{
    if (!(*this))
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__,
                                            __FUNCTION__);

    if (offset + MIN_INDEX - 1 > this->index)
        throw ErrorMatrixIteratorLimitViolation(__FILE__, __LINE__,
                                                   __FUNCTION__);

    this->index -= offset;

    return *this;
}

template <typename Type>
int MatrixIterator<Type>::compare(const MatrixIterator<Type> &iter) const
{
    if (!(*this) || !iter)
        throw ErrorMatrixIteratorNullPointer(__FILE__, __LINE__,
                                                __FUNCTION__);

    if (this->isExpired() || iter.isExpired())
        throw ErrorMatrixIteratorExpired(__FILE__, __LINE__, __FUNCTION__);

    if (this->index == iter.index)
        return 0;

    if (this->index > iter.index)
        return 1;

    return -1;
}

template <typename Type>
bool MatrixIterator<Type>::operator == (const MatrixIterator<Type> &iter)
     const
{
    return 0 == this->compare(iter);
}

template <typename Type>
bool MatrixIterator<Type>::operator != (const MatrixIterator<Type> &iter)
     const
{
    return 0 != this->compare(iter);
}

template <typename Type>
bool MatrixIterator<Type>::operator >= (const MatrixIterator<Type> &iter)
     const
{
    return 0 <= this->compare(iter);
}

template <typename Type>
bool MatrixIterator<Type>::operator <= (const MatrixIterator<Type> &iter)
     const
{
    return 0 >= this->compare(iter);
}

template <typename Type>
bool MatrixIterator<Type>::operator > (const MatrixIterator<Type> &iter)
     const
{
    return 0 < this->compare(iter);
}

template <typename Type>
bool MatrixIterator<Type>::operator < (const MatrixIterator<Type> &iter)
     const
{
    return 0 > this->compare(iter);
}

template <typename Type>
void MatrixIterator<Type>::set_ptr(const std::weak_ptr<MatrixRow<Type>[]> &ptr)
{
    this->ptr = ptr;
}

template <typename Type>
void MatrixIterator<Type>::set_index(const size_t index)
{
    this->index = index + MIN_INDEX;
}

template <typename Type>
void MatrixIterator<Type>::set_size(const size_t size)
{
    this->size = size + MIN_INDEX;
}

template <typename Type>
void MatrixIterator<Type>::set_iter(const MatrixIterator<Type> &iter)
{
    this->ptr = iter.ptr;
    this->index = iter.index;
    this->size = iter.size;
}

template <typename Type>
ConstMatrixIterator<Type>::ConstMatrixIterator(const Matrix<Type> &matrix)
: MatrixIterator<Type>::MatrixIterator()
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
ConstMatrixIterator<Type>::ConstMatrixIterator(const ConstMatrixIterator<Type> &iter)
: MatrixIterator<Type>::MatrixIterator(iter) {}

template <typename Type>
ConstMatrixIterator<Type>::ConstMatrixIterator(ConstMatrixIterator<Type> &&iter)
: MatrixIterator<Type>::MatrixIterator(iter) {}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator = (const ConstMatrixIterator<Type> &iter)
{
    this->MatrixIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator = (const Matrix<Type> &matrix)
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
const MatrixRow<Type> &ConstMatrixIterator<Type>::operator * (void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
const MatrixRow<Type> &ConstMatrixIterator<Type>::get(void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator ++ (void)
{
    this->MatrixIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ConstMatrixIterator<Type> ConstMatrixIterator<Type>::operator ++ (int)
{
    ConstMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator -- (void)
{
    this->MatrixIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ConstMatrixIterator<Type> ConstMatrixIterator<Type>::operator -- (int)
{
    ConstMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator += (const size_t offset)
{
    this->MatrixIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ConstMatrixIterator<Type> ConstMatrixIterator<Type>::operator + (const size_t offset) const
{
    ConstMatrixIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ConstMatrixIterator<Type> ConstMatrixIterator<Type>::operator - (const size_t offset) const
{
    ConstMatrixIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

template <typename Type>
ReverseMatrixIterator<Type>::ReverseMatrixIterator(Matrix<Type> &matrix)
: MatrixIterator<Type>::MatrixIterator()
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_index(matrix.size - 1);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
ReverseMatrixIterator<Type>::ReverseMatrixIterator(const ReverseMatrixIterator<Type> &iter)
: MatrixIterator<Type>::MatrixIterator(iter) {}

template <typename Type>
ReverseMatrixIterator<Type>::ReverseMatrixIterator(ReverseMatrixIterator<Type> &&iter)
: MatrixIterator<Type>::MatrixIterator(iter) {}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator = (const ReverseMatrixIterator<Type> &iter)
{
    this->MatrixIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator = (Matrix<Type> &matrix)
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_index(matrix.size - 1);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
MatrixRow<Type> &ReverseMatrixIterator<Type>::operator * (void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
MatrixRow<Type> &ReverseMatrixIterator<Type>::get(void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator ++ (void)
{
    this->MatrixIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ReverseMatrixIterator<Type> ReverseMatrixIterator<Type>::operator ++ (int)
{
    ReverseMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator -- (void)
{
    this->MatrixIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ReverseMatrixIterator<Type> ReverseMatrixIterator<Type>::operator -- (int)
{
    ReverseMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator += (const size_t offset)
{
    this->MatrixIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ReverseMatrixIterator<Type> ReverseMatrixIterator<Type>::operator + (const size_t offset) const
{
    ReverseMatrixIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ReverseMatrixIterator<Type> ReverseMatrixIterator<Type>::operator - (const size_t offset) const
{
    ReverseMatrixIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

template <typename Type>
bool ReverseMatrixIterator<Type>::operator >= (const ReverseMatrixIterator<Type> &iter) const
{
    return this->MatrixIterator<Type>::operator <= (iter);
}

template <typename Type>
bool ReverseMatrixIterator<Type>::operator <= (const ReverseMatrixIterator<Type> &iter) const
{
    return this->MatrixIterator<Type>::operator >= (iter);
}

template <typename Type>
bool ReverseMatrixIterator<Type>::operator > (const ReverseMatrixIterator<Type> &iter) const
{
    return this->MatrixIterator<Type>::operator < (iter);
}

template <typename Type>
bool ReverseMatrixIterator<Type>::operator < (const ReverseMatrixIterator<Type> &iter) const
{
    return this->MatrixIterator<Type>::operator > (iter);
}

template <typename Type>
ConstReverseMatrixIterator<Type>::ConstReverseMatrixIterator(const Matrix<Type> &matrix)
: ReverseMatrixIterator<Type>::ReverseMatrixIterator()
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_index(matrix.size - 1);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
ConstReverseMatrixIterator<Type>::ConstReverseMatrixIterator(const ConstReverseMatrixIterator<Type> &iter)
: ReverseMatrixIterator<Type>::ReverseMatrixIterator(iter) {}

template <typename Type>
ConstReverseMatrixIterator<Type>::ConstReverseMatrixIterator(ConstReverseMatrixIterator<Type> &&iter)
: ReverseMatrixIterator<Type>::ReverseMatrixIterator(iter) {}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator = (const ConstReverseMatrixIterator<Type> &iter)
{
    this->MatrixIterator<Type>::set_iter(iter);

    return *this;
}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator = (const Matrix<Type> &matrix)
{
    std::weak_ptr<MatrixRow<Type>[]> ptr = matrix.data;
    this->MatrixIterator<Type>::set_ptr(ptr);
    this->MatrixIterator<Type>::set_index(matrix.size - 1);
    this->MatrixIterator<Type>::set_size(matrix.size);
}

template <typename Type>
const MatrixRow<Type> &ConstReverseMatrixIterator<Type>::operator * (void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
const MatrixRow<Type> &ConstReverseMatrixIterator<Type>::get(void)
{
    return this->MatrixIterator<Type>::get();
}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator ++ (void)
{
    this->MatrixIterator<Type>::operator -- ();

    return *this;
}

template <typename Type>
ConstReverseMatrixIterator<Type> ConstReverseMatrixIterator<Type>::operator ++ (int)
{
    ConstReverseMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator -- (1);

    return tmp;
}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator -- (void)
{
    this->MatrixIterator<Type>::operator ++ ();

    return *this;
}

template <typename Type>
ConstReverseMatrixIterator<Type> ConstReverseMatrixIterator<Type>::operator -- (int)
{
    ConstReverseMatrixIterator<Type> tmp(*this);
    this->MatrixIterator<Type>::operator ++ (1);

    return tmp;
}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator += (const size_t offset)
{
    this->MatrixIterator<Type>::operator -= (offset);

    return *this;
}

template <typename Type>
ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator -= (const size_t offset)
{
    this->MatrixIterator<Type>::operator += (offset);

    return *this;
}

template <typename Type>
ConstReverseMatrixIterator<Type> ConstReverseMatrixIterator<Type>::operator + (const size_t offset) const
{
    ConstReverseMatrixIterator<Type> tmp(*this);
    tmp += offset;

    return tmp;
}

template <typename Type>
ConstReverseMatrixIterator<Type> ConstReverseMatrixIterator<Type>::operator - (const size_t offset) const
{
    ConstReverseMatrixIterator<Type> tmp(*this);
    tmp -= offset;

    return tmp;
}

#endif

