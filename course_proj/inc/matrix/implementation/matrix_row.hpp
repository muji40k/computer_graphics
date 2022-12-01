#ifndef _MATRIX_ROW_HPP_
#define _MATRIX_ROW_HPP_

#include <cmath>

#include "matrix_row.h"

#include "common_exceptions.h"
#include "matrix_row_exceptions.h"

#define EPS 1e-8

template <typename Type>
MatrixRow<Type>::MatrixRow(void)
{
    this->data = nullptr;
    this->size = 0;
}

template <typename Type>
MatrixRow<Type>::MatrixRow(const MatrixRow<Type> &row)
{
    this->data = MatrixRow<Type>::allocate_copy(row.data, row.size);
    this->size = row.size;
}

template <typename Type>
MatrixRow<Type>::MatrixRow(MatrixRow<Type> &&row)
{
    this->data = row.data;
    this->size = row.size;
    row->data = nullptr;
}

template <typename Type>
MatrixRow<Type>::MatrixRow(std::shared_ptr<Type[]> row, const size_t size)
{
    this->data = MatrixRow<Type>::allocate_row(size);
    this->size = size;

    for (size_t i = 0; this->size > i; i++)
        this->data[i] = row[i];
}

template <typename Type>
MatrixRow<Type>::MatrixRow(const size_t size, const Type &value)
{
    this->data = MatrixRow<Type>::allocate_row(size);
    this->size = size;

    this->fill(value);
}

template <typename Type>
MatrixRow<Type>::MatrixRow(const std::initializer_list<Type> array)
{
    this->data = MatrixRow<Type>::allocate_row(array.size());
    this->size = array.size();

    size_t i = 0;

    for (Type value : array)
        (*this)[i++] = value;
}

template <typename Type>
MatrixRow<Type>::MatrixRow(const Type *array, const size_t size)
{
    this->data = MatrixRow<Type>::allocate_row(size);
    this->size = size;

    for (size_t i = 0; size > i; i++)
        (*this)[i] = array[i];
}

template <typename Type>
template <typename Iter>
MatrixRow<Type>::MatrixRow(const Iter start, const Iter end)
{
    this->data = nullptr;
    this->size = 0;

    for (Iter iter = start; end != iter; ++iter)
        this->append(*iter);
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator = (const MatrixRow<Type> &row)
{
    this->data = MatrixRow<Type>::allocate_copy(row.data, row.size);
    this->size = row.size;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator = (const std::initializer_list<Type> array)
{
    this->data = MatrixRow<Type>::allocate_row(array.size());
    this->size = array.size();

    size_t i = 0;

    for (Type value : array)
        (*this)[i++] = value;

    return *this;
}

template <typename Type>
MatrixRow<Type>::operator bool(void) const
{
    return nullptr != this->data;
}

template <typename Type>
bool MatrixRow<Type>::isEmpty(void) const
{
    bool empty = this->BaseContainer::isEmpty();

    if (!(*this) && !empty)
        throw ErrorMatrixRowNullPointer(__FILE__, __LINE__, __FUNCTION__);

    return empty;
}

template <typename Type>
Type &MatrixRow<Type>::get(const size_t index)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= index)
        throw ErrorMatrixRowIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    return this->data[index];
}

template <typename Type>
Type &MatrixRow<Type>::operator [] (const size_t index)
{
    return this->get(index);
}

template <typename Type>
const Type &MatrixRow<Type>::get(const size_t index) const
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= index)
        throw ErrorMatrixRowIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    return this->data[index];
}

template <typename Type>
const Type &MatrixRow<Type>::operator [] (const size_t index) const
{
    return this->get(index);
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::copy(void)
{
    return MatrixRow<Type> (*this);
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::fill(const Type &value)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (Type &i : (*this))
        i = value; 

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::swap(const size_t column1,
                                       const size_t column2)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= column1 || this->size <= column2)
        throw ErrorMatrixRowIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    Type tmp = (*this)[column1];
    (*this)[column1] = (*this)[column2];
    (*this)[column2] = tmp;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::insert(const Type &data, const size_t index)
{
    if (this->size < index)
        throw ErrorMatrixRowIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    std::shared_ptr<Type[]> ext = MatrixRow<Type>::allocate_row(this->size + 1);
    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    ext[i++] = data;

    for (; this->size + 1 > i; i++)
        ext[i] = (*this)[i - 1];

    this->size++;
    this->data = ext;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::append(const Type &data)
{
    return this->insert(data, this->size);
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::remove(const size_t index)
{
    if (0 == this->size)
        throw ErrorMatrixRowIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    std::shared_ptr<Type[]> ext = MatrixRow<Type>::allocate_row(this->size - 1);
    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    for (; this->size - 1 > i; i++)
        ext[i] = (*this)[i + 1];

    this->size--;
    this->data = ext;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::sort(int (&compare)(const Type &,
                                                      const Type &))
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    Type tmp;

    for (size_t i = 1, j = 0; this->size > i; j = i++)
    {
        tmp = (*this)[i];

        for (; 0 < j && 0 > compare(tmp, (*this)[j]); j--)
            (*this)[j + 1] = (*this)[j];

        if (0 != j || 0 <= compare(tmp, (*this)[j]))
            (*this)[j + 1] = tmp;
        else
        {
            (*this)[j + 1] = (*this)[j];
            (*this)[j] = tmp;
        }
    }

    return *this;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::sorted(int (&compare)(const Type &, const Type &))
                const
{
    MatrixRow<Type> out(*this);

    return out.sort(compare);
}

template <typename Type>
bool MatrixRow<Type>::isEqual(const MatrixRow<Type> &row) const
{
    if (this->isEmpty() || row.isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != row.size)
        return false;

    bool same = true;

    for (size_t i = 0; same && this->size > i; i++)
        same = ((*this)[i] == row[i]);

    return same;
}

template <typename Type>
bool MatrixRow<Type>::operator == (const MatrixRow<Type> &row) const
{
    return this->isEqual(row);
}

template <typename Type>
bool MatrixRow<Type>::operator != (const MatrixRow<Type> &row) const
{
    return !this->isEqual(row);
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator + (const MatrixRow<Type> &row) const
{
    MatrixRow<Type> tmp(*this);

    return tmp += row;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator + (const Type &data) const
{
    MatrixRow<Type> tmp(*this);

    return tmp += data;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator - (const MatrixRow<Type> &row) const
{
    MatrixRow<Type> tmp(*this);

    return tmp -= row;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator - (const Type &data) const
{
    MatrixRow<Type> tmp(*this);

    return tmp -= data;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator * (const Type &data) const
{
    MatrixRow<Type> tmp(*this);

    return tmp *= data;
}

template <typename Type>
MatrixRow<Type> MatrixRow<Type>::operator / (const Type &data) const
{
    MatrixRow<Type> tmp(*this);

    return tmp /= data;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator += (const MatrixRow<Type> &row)
{
    if (this->isEmpty() || row.isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != row.size)
        throw ErrorMatrixRowIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] += row[i];

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator += (const Type &data)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] += data;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator -= (const MatrixRow<Type> &row)
{
    if (this->isEmpty() || row.isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != row.size)
        throw ErrorMatrixRowIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] -= row[i];

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator -= (const Type &data)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] -= data;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator *= (const Type &data)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] *= data;

    return *this;
}

template <typename Type>
MatrixRow<Type> &MatrixRow<Type>::operator /= (const Type &data)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (Type() == data)
        throw ErrorDivisionByZero(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] /= data;

    return *this;
}

template <typename Type>
MatrixRowIterator<Type> MatrixRow<Type>::begin(void)
{
    return MatrixRowIterator<Type> (*this);
}

template <typename Type>
MatrixRowIterator<Type> MatrixRow<Type>::end(void)
{
    return MatrixRowIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstMatrixRowIterator<Type> MatrixRow<Type>::begin(void) const
{
    return ConstMatrixRowIterator<Type> (*this);
}

template <typename Type>
ConstMatrixRowIterator<Type> MatrixRow<Type>::end(void) const
{
    return ConstMatrixRowIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstMatrixRowIterator<Type> MatrixRow<Type>::cbegin(void)
{
    return ConstMatrixRowIterator<Type> (*this);
}

template <typename Type>
ConstMatrixRowIterator<Type> MatrixRow<Type>::cend(void)
{
    return ConstMatrixRowIterator<Type> (*this) + this->size;
}

template <typename Type>
ReverseMatrixRowIterator<Type> MatrixRow<Type>::rbegin(void)
{
    return ReverseMatrixRowIterator<Type> (*this);
}

template <typename Type>
ReverseMatrixRowIterator<Type> MatrixRow<Type>::rend(void)
{
    return ReverseMatrixRowIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> MatrixRow<Type>::crbegin(void)
{
    return ConstReverseMatrixRowIterator<Type> (*this);
}

template <typename Type>
ConstReverseMatrixRowIterator<Type> MatrixRow<Type>::crend(void)
{
    return ConstReverseMatrixRowIterator<Type> (*this) + this->size;
}

template <typename Type>
std::shared_ptr<Type[]> MatrixRow<Type>::allocate_row(const size_t size)
{
    if (0 == size)
        throw ErrorMatrixRowEmptyAllocation(__FILE__, __LINE__, __FUNCTION__);

    try
    {
        std::shared_ptr<Type[]> out = nullptr;
        out.reset(new Type[size]);

        return out;
    }
    catch (std::bad_alloc &err)
    {
        throw ErrorMatrixRowAllocation(__FILE__, __LINE__, __FUNCTION__);
    }
}

template <typename Type>
std::shared_ptr<Type[]> MatrixRow<Type>::allocate_copy(const std::shared_ptr<Type[]> ptr,
                                                       const size_t size)
{
    if (0 == size)
        throw ErrorMatrixRowEmptyAllocation(__FILE__, __LINE__, __FUNCTION__);

    if (nullptr == ptr)
        throw ErrorMatrixRowNullPointer(__FILE__, __LINE__, __FUNCTION__);

    try
    {
        std::shared_ptr<Type[]> out = nullptr;
        out.reset(new Type[size]);

        for (size_t i = 0; size > i; i++)
            out[i] = ptr[i];

        return out;
    }
    catch (std::bad_alloc &err)
    {
        throw ErrorMatrixRowAllocation(__FILE__, __LINE__, __FUNCTION__);
    }
}

template <typename Type>
std::ostream &operator << (std::ostream &stream, const MatrixRow<Type> &row)
{
    for (const Type &val : row)
        stream << val << " ";

    return stream;
}

template <typename Type>
MatrixRow<Type> operator + (const Type &value, const MatrixRow<Type> &row)
{
    return row + value;
}

template <typename Type>
MatrixRow<Type> operator - (const Type &value, const MatrixRow<Type> &row)
{
    return row - value;
}

template <typename Type>
MatrixRow<Type> operator * (const Type &value, const MatrixRow<Type> &row)
{
    return row * value;
}

template <typename Type>
Type find_min(const MatrixRow<Type> &row)
{
    Type min = row[0];

    for (const Type value : row)
        if (value < min)
            min = value;

    return min;
}

template <typename Type>
Type find_max(const MatrixRow<Type> &row)
{
    Type max = row[0];

    for (const Type value : row)
        if (value > max)
            max = value;

    return max;
}

template <typename Type>
Type find_sum(const MatrixRow<Type> &row)
{
    Type result = Type();

    for (const Type value : row)
        result += value;

    return result;
}

#endif

