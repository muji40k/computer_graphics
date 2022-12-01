#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "matrix.h"
#include "matrix_exceptions.h"

template <typename Type>
Matrix<Type>::Matrix(void)
{
    this->data = nullptr;
    this->size = 0;
    this->row_size = 0;
}

template <typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &matrix)
{
    this->data = Matrix<Type>::allocate_copy(matrix.data, matrix.size,
                                             matrix.row_size);
    this->size = matrix.size;
    this->row_size = matrix.row_size;
}

template <typename Type>
Matrix<Type>::Matrix(Matrix<Type> &&matrix)
{
    this->size = matrix.size;
    this->row_size = matrix.row_size;
    this->data = matrix.data;
    matrix.data = nullptr;
    matrix.size = 0;
    matrix.row_size = 0;
}

template <typename Type>
Matrix<Type>::Matrix(const size_t rows, const size_t columns,
                     const Type &value)
{
    this->data = Matrix<Type>::allocate_matrix(rows, columns);
    this->size = rows;
    this->row_size = columns;
    this->fill(value);
}

template <typename Type>
Matrix<Type>::Matrix(const_initializer_matrix<Type> matrix)
{
    this->size = matrix.size();
    this->row_size = matrix.begin()->size();
    this->data = Matrix<Type>::allocate_matrix(this->size, this->row_size);

    for (size_t i = 0; this->size > i; i++)
    {
        if (std::data(matrix)[i].size() != this->row_size)
            throw ErrorMatrixOddInitialization(__FILE__, __LINE__,
                                               __FUNCTION__);

        (*this)[i] = std::data(matrix)[i];
    }
}

template <typename Type>
Matrix<Type>::Matrix(const Type **matrix, const size_t rows,
                     const size_t columns)
{
    if (nullptr == matrix)
        throw ErrorMatrixNullPointer(__FILE__, __LINE__, __FUNCTION__);

    this->data = nullptr;
    this->size = 0;

    for (size_t i = 0; rows > i; i++)
        this->appendRow(MatrixRow<Type> (matrix[i], columns));
}

template <typename Type>
template <typename Iter>
Matrix<Type>::Matrix(const Iter begin, const Iter end)
{
    this->data = nullptr;
    this->size = 0;

    for (Iter iter = begin; end != iter; ++iter)
        this->appendRow(MatrixRow<Type>((*iter).begin(), (*iter).end()));
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator = (const Matrix<Type> &matrix)
{
    this->data = Matrix<Type>::allocate_copy(matrix.data, matrix.size,
                                             matrix.row_size);
    this->size = matrix.size;
    this->row_size = matrix.row_size;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator = (const_initializer_matrix<Type> matrix)
{
    this->size = matrix.size();
    this->row_size = matrix.begin().size();
    this->data = Matrix<Type>::allocate_matrix(this->size, this->row_size);

    for (size_t i = 0; this->size > i; i++)
    {
        if (std::data(matrix)[i].size() != this->row_size)
            throw ErrorMatrixOddInitialization(__FILE__, __LINE__,
                                               __FUNCTION__);

        (*this)[i] = std::data(matrix)[i];
    }
}

template <typename Type>
size_t Matrix<Type>::getRows(void)
{
    return this->size;
}

template <typename Type>
size_t Matrix<Type>::getColumns(void)
{
    return this->row_size;
}

template <typename Type>
Matrix<Type>::operator bool(void) const
{
    return nullptr != this->data;
}

template <typename Type>
bool Matrix<Type>::isEmpty(void) const
{
    bool empty = this->BaseContainer::isEmpty() || 0 == this->row_size;

    if (!(*this) && !empty)
        throw ErrorMatrixRowNullPointer(__FILE__, __LINE__, __FUNCTION__);

    return empty;
}

template <typename Type>
MatrixRow<Type> &Matrix<Type>::getRow(const size_t index)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    return this->data[index];
}

template <typename Type>
MatrixRow<Type> &Matrix<Type>::operator [] (const size_t index)
{
    return this->getRow(index);
}

template <typename Type>
const MatrixRow<Type> &Matrix<Type>::getRow(const size_t index) const
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    return this->data[index];
}

template <typename Type>
const MatrixRow<Type> &Matrix<Type>::operator [] (const size_t index) const
{
    return this->getRow(index);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::fill(const Type &value)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row.fill(value);

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::copy(void)
{
    Matrix<Type> out (*this);

    return out;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::swapColumns(const size_t column1, const size_t column2)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->row_size <= column1 || this->row_size < column2)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row.swap(column1, column2);

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::swapRows(const size_t row1, const size_t row2)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= row1 || this->size < row2)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    MatrixRow<Type> tmp = (*this)[row1];
    (*this)[row1] = (*this)[row2];
    (*this)[row2] = tmp;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertRow(const size_t index,
                                      const shared_ptr<Type[]> row,
                                      const size_t size)
{
    if (this->size < index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    if (this->isEmpty())
        this->row_size = size;
    else if (this->row_size != size)
        throw ErrorMatrixInsertionIncompatible(__FILE__, __LINE__,
                                               __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> ext = Matrix<Type>::allocate_matrix(this->size + 1,
                                                                           this->row_size);
    MatrixRow<Type> tmp(row, size);

    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    ext[i++] = tmp;

    for (; this->size + 1 > i; i++)
        ext[i] = (*this)[i - 1];

    this->size++;
    this->data = ext;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertRow(const size_t index,
                                      const initializer_list<Type> row)
{
    if (this->size < index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    if (this->isEmpty())
        this->row_size = row.size();
    else if (this->row_size != row.size())
        throw ErrorMatrixInsertionIncompatible(__FILE__, __LINE__,
                                               __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> ext = Matrix<Type>::allocate_matrix(this->size + 1,
                                                                         this->row_size);
    MatrixRow<Type> tmp(row);

    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    ext[i++] = tmp;

    for (; this->size + 1 > i; i++)
        ext[i] = (*this)[i - 1];

    this->size++;
    this->data = ext;

    return *this;
}


template <typename Type>
Matrix<Type> &Matrix<Type>::insertRow(const size_t index,
                                      const MatrixRow<Type> &row)
{
    if (this->size < index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    if (this->isEmpty())
        this->row_size = row.getSize();
    else if (this->row_size != row.getSize())
        throw ErrorMatrixInsertionIncompatible(__FILE__, __LINE__,
                                               __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> ext = Matrix<Type>::allocate_matrix(this->size + 1,
                                                                         this->row_size);
    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    ext[i++] = row;

    for (; this->size + 1 > i; i++)
        ext[i] = (*this)[i - 1];

    this->size++;
    this->data = ext;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertRow(const size_t index, const Type &value)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size < index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> ext = Matrix<Type>::allocate_matrix(this->size + 1,
                                                                         this->row_size);
    MatrixRow<Type> tmp(this->row_size, value);
    size_t i = 0;

    for (; index > i; i++)
        ext[i] = (*this)[i];

    ext[i++] = tmp;

    for (; this->size + 1 > i; i++)
        ext[i] = (*this)[i - 1];

    this->size++;
    this->data = ext;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertColumn(const size_t index,
                                         const shared_ptr<Type[]> column,
                                         const size_t size)
{
    if (this->isEmpty())
    {
        this->size = size;
        this->data = Matrix<Type>::allocate_matrix(size, 0);
    }
    else if (this->size != size)
        throw ErrorMatrixInsertionIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i].insert(column[i], index);

    this->row_size++;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertColumn(const size_t index,
                                         const initializer_list<Type> column)
{
    if (this->isEmpty())
    {
        this->size = size;
        this->data = Matrix<Type>::allocate_matrix(size, 0);
    }
    else if (this->size != column.size())
        throw ErrorMatrixInsertionIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i].insert(std::data(column)[i], index);

    this->row_size++;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::insertColumn(const size_t index,
                                         const Type &value)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i].insert(value, index);

    this->row_size++;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendRow(const shared_ptr<Type[]> row,
                                      const size_t size)
{
    return this->insertRow(this->size, row, size);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendRow(const initializer_list<Type> row)
{
    return this->insertRow(this->size, row);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendRow(const MatrixRow<Type> &row)
{
    return this->insertRow(this->size, row);
}

template <typename Type> Matrix<Type> &Matrix<Type>::appendRow(const Type &value)
{
    return this->insertRow(this->size, value);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendColumn(const shared_ptr<Type[]> column,
                                         const size_t size)
{
    return this->insertColumn(this->row_size, column, size);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendColumn(const initializer_list<Type> column)
{
    return this->insertColumn(this->row_size, column);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::appendColumn(const Type &value)
{
    return this->insertColumn(this->row_size, value);
}

template <typename Type>
Matrix<Type> &Matrix<Type>::removeColumn(const size_t index)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->row_size <= index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    if (this->row_size != 1)
    {
        for (MatrixRow<Type> &row : *this)
            row.remove(index);

        this->row_size--;
    }
    else
    {
        this->data = nullptr;
        this->size = 0;
        this->row_size = 0;
    }

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::removeRow(const size_t index)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size <= index)
        throw ErrorMatrixIndexViolation(__FILE__, __LINE__, __FUNCTION__);

    if (this->size == 1)
    {
        this->data = nullptr;
        this->size = 0;
        this->row_size = 0;
    }
    else
    {
        std::shared_ptr<MatrixRow<Type>[]> ext = Matrix<Type>::allocate_matrix(this->size - 1,
                                                                               this->row_size);
        size_t i = 0;

        for (; index > i; i++)
            ext[i] = (*this)[i];

        for (; this->size - 1 > i; i++)
            ext[i] = (*this)[i + 1];

        this->size--;
        this->data = ext;
    }

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::sortColumns(int (&compare)(const Type &, const Type &))
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    Type tmp;

    for (size_t k = 0; this->row_size > k; k++)
        for (size_t i = 1, j = 0; this->size > i; j = i++)
        {
            tmp = (*this)[i][k];

            for (; 0 < j && 0 > compare(tmp, (*this)[j][k]); j--)
                (*this)[j + 1][k] = (*this)[j][k];

            if (0 != j || 0 <= compare(tmp, (*this)[j][k]))
                (*this)[j + 1][k] = tmp;
            else
            {
                (*this)[j + 1][k] = (*this)[j][k];
                (*this)[j][k] = tmp;
            }
        }

    return *this;

}

template <typename Type>
Matrix<Type> &Matrix<Type>::sortRows(int (&compare)(const Type &, const Type &))
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row.sort(compare);

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::sortByColumn(const size_t index,
                                         int (&compare)(const Type &, const Type &))
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    MatrixRow<Type> tmp;

    for (size_t i = 1, j = 0; this->size > i; j = i++)
    {
        tmp = (*this)[i];

        for (; 0 < j && 0 > compare(tmp[index], (*this)[j][index]); j--)
            (*this)[j + 1] = (*this)[j];

        if (0 != j || 0 <= compare(tmp[index], (*this)[j][index]))
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
Matrix<Type> &Matrix<Type>::sortByRow(const size_t index,
                                      int (&compare)(const Type &, const Type &))
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 1, j = 0; this->row_size > i; j = i++)
    {
        for (; 0 < j && 0 > compare((*this)[index][j + 1], (*this)[index][j]); j--)
            this->swapColumns(j, j + 1);

        if (0 == j && 0 > compare((*this)[index][j + 1], (*this)[index][j]))
            this->swapColumns(j, j + 1);
    }

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::sortedColumns(int (&compare)(const Type &, const Type &))
             const
{
    Matrix<Type> out(*this);

    return out.sortColumns(compare);
}

template <typename Type>
Matrix<Type> Matrix<Type>::sortedRows(int (&compare)(const Type &, const Type &))
             const
{
    Matrix<Type> out(*this);

    return out.sortRows(compare);
}

template <typename Type>
Matrix<Type> Matrix<Type>::sortedByColumn(const size_t index,
                                          int (&compare)(const Type &, const Type &))
             const
{
    Matrix<Type> out(*this);

    return out.sortByColumn(index, compare);
}

template <typename Type>
Matrix<Type> Matrix<Type>::sortedByRow(const size_t index,
                                       int (&compare)(const Type &, const Type &))
             const
{
    Matrix<Type> out(*this);

    return out.sortByRow(index, compare);
}

template <typename Type>
bool Matrix<Type>::isEqual(const Matrix<Type> &matrix) const
{
    if (this->isEmpty() || matrix.isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != matrix.size || this->row_size != matrix.row_size)
        return false;

    bool same = true;

    for (size_t i = 0; same && this->size > i; i++)
        same = (*this)[i].isEqual(matrix[i]);

    return same;
}

template <typename Type>
bool Matrix<Type>::operator == (const Matrix<Type> &matrix) const
{
    return this->isEqual(matrix);
}

template <typename Type>
bool Matrix<Type>::operator != (const Matrix<Type> &matrix) const
{
    return !this->isEqual(matrix);
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator + (const Matrix<Type> &matrix) const
{
    Matrix<Type> out(*this);

    return out += matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator + (const Type data) const
{
    Matrix<Type> out(*this);

    return out += data;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator - (const Matrix<Type> &matrix) const
{
    Matrix<Type> out(*this);

    return out -= matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator - (const Type data) const
{
    Matrix<Type> out(*this);

    return out -= data;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator * (const Matrix<Type> &matrix) const
{
    Matrix<Type> out(*this);

    return out *= matrix;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator * (const Type data) const
{
    Matrix<Type> out(*this);

    return out *= data;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator / (const Type data) const
{
    Matrix<Type> out(*this);

    return out /= data;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator += (const Matrix<Type> &matrix)
{
    if (this->isEmpty() || matrix.isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != matrix.size || this->row_size != matrix.row_size)
        throw ErrorMatrixIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] += matrix[i];

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator += (const Type data)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row += data;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator -= (const Matrix<Type> &matrix)
{
    if (this->isEmpty() || matrix.isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != matrix.size || this->row_size != matrix.row_size)
        throw ErrorMatrixIncompatible(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] -= matrix[i];

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator -= (const Type data)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row -= data;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator *= (const Matrix<Type> &matrix)
{
    if (this->isEmpty() || matrix.isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->row_size != matrix.size)
        throw ErrorMatrixIncompatible(__FILE__, __LINE__, __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> out = Matrix<Type>::allocate_matrix(this->size,
                                                                           matrix.row_size);

    for (size_t i = 0; this->size > i; i++)
        for (size_t j = 0; matrix.row_size > j; j++)
            for (size_t k = 0; this->row_size > k; k++)
                out[i][j] += (*this)[i][k] * matrix[k][j];

    this->data = out;
    this->row_size = matrix.row_size;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator *= (const Type data)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row *= data;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::operator /= (const Type data)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    for (MatrixRow<Type> &row : *this)
        row /= data;

    return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::getTransposed(void) const
{
    Matrix<Type> out(*this);

    return out.transpose();
}

template <typename Type>
Matrix<Type> Matrix<Type>::getInversed(void)   const
{
    Matrix<Type> out(*this);

    return out.inverse();
}

template <typename Type>
Matrix<Type> &Matrix<Type>::transpose(void)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    std::shared_ptr<MatrixRow<Type>[]> out = Matrix<Type>::allocate_matrix(this->row_size,
                                                                           this->size);

    for (size_t i = 0; this->size > i; i++)
        for (size_t j = 0; this->row_size > j; j++)
            out[j][i] = (*this)[i][j];

    this->data = out;
    size_t tmp = this->size;
    this->size = this->row_size;
    this->row_size = tmp;

    return *this;
}

template <typename Type>
Matrix<Type> &Matrix<Type>::inverse(void)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != this->row_size)
        throw ErrorMatrixNonSquare(__FILE__, __LINE__, __FUNCTION__);

    Type det = this->determinant();

    if (Type() == det)
        throw ErrorMatrixNoInverted(__FILE__, __LINE__, __FUNCTION__);

    Matrix<Type> copy;
    std::shared_ptr<MatrixRow<Type>[]> out = Matrix<Type>::allocate_matrix(this->size,
                                                                           this->row_size);

    for (size_t i = 0; this->size > i; i++)
        for (size_t j = 0; this->row_size > j; j++)
        {
            copy = *this;
            copy.removeColumn(j);
            copy.removeRow(i);

            out[j][i] = copy.determinant() / det;

            if (1 == (i + j) % 2)
                out[j][i] *= -1;
        }

    this->data = out;

    return *this;
}

template <typename Type>
Type Matrix<Type>::determinant(void) const
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != this->row_size)
        throw ErrorMatrixNonSquare(__FILE__, __LINE__, __FUNCTION__);

    Matrix<Type> tmp(*this);
    Type result = Type();
    size_t swaps;

    try
    {
        swaps = tmp.descendingGauss();

        result = tmp[0][0];

        for (size_t i = 1; tmp.size > i; i++)
            result *= tmp[i][i];

        if (1 == swaps % 2)
            result *= -1;
    }
    catch (ErrorMatrixNoSolution &err)
    {
        result = Type();
    }

    return result;
}

template <typename Type>
std::shared_ptr<Type[]> Matrix<Type>::solveLinearSystem(void) const
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if ((this->size + 1) != this->row_size)
        throw ErrorMatrixNoSolution(__FILE__, __LINE__, __FUNCTION__);

    Matrix<Type> tmp (*this);
    tmp.descendingGauss();

    for (size_t i = tmp.size - 1; 0 != i; i--)
        for (size_t j = i; tmp.size > j; j++)
            tmp[i - 1] -= tmp[i - 1][j] / tmp[j][j] * tmp[j];

    try
    {
        std::shared_ptr<Type[]> out (new Type[tmp.size]);

        for (size_t i = 0; tmp.size > i; i++)
            out[i] = tmp[i][tmp.size] / tmp[i][i];

        return out;
    }
    catch (std::bad_alloc &err)
    {
        throw ErrorMatrixAllocationSolution(__FILE__, __LINE__, __FUNCTION__);
    }
}

template <typename Type>
MatrixIterator<Type> Matrix<Type>::begin(void)
{
    return MatrixIterator<Type> (*this);
}

template <typename Type>
MatrixIterator<Type> Matrix<Type>::end(void)
{
    return MatrixIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstMatrixIterator<Type> Matrix<Type>::begin(void) const
{
    return ConstMatrixIterator<Type> (*this);
}

template <typename Type>
ConstMatrixIterator<Type> Matrix<Type>::end(void) const
{
    return ConstMatrixIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstMatrixIterator<Type> Matrix<Type>::cbegin(void)
{
    return ConstMatrixIterator<Type> (*this);
}

template <typename Type>
ConstMatrixIterator<Type> Matrix<Type>::cend(void)
{
    return ConstMatrixIterator<Type> (*this) + this->size;
}

template <typename Type>
ReverseMatrixIterator<Type> Matrix<Type>::rbegin(void)
{
    return ReverseMatrixIterator<Type> (*this);
}

template <typename Type>
ReverseMatrixIterator<Type> Matrix<Type>::rend(void)
{
    return ReverseMatrixIterator<Type> (*this) + this->size;
}

template <typename Type>
ConstReverseMatrixIterator<Type> Matrix<Type>::crbegin(void)
{
    return ConstReverseMatrixIterator<Type> (*this);
}

template <typename Type>
ConstReverseMatrixIterator<Type> Matrix<Type>::crend(void)
{
    return ConstReverseMatrixIterator<Type> (*this) + this->size;
}

template <typename Type>
size_t Matrix<Type>::descendingGauss(void)
{
    Matrix<Type> copy (*this), out (1, this->getColumns());
    size_t swaps = 0;

    size_t i = 0, k = 0;

    do
    {
        for (; k < copy.size && Type() == copy[k][0]; k++);

        if (copy.size == k)
            throw ErrorMatrixNoSolution(__FILE__, __LINE__, __FUNCTION__);

        if (0 != k)
        {
            copy.swapRows(0, k);
            swaps++;
        }

        for (size_t j = 1; copy.size > j; j++)
            copy[j] -= copy[j][0] / copy[0][0] * copy[0];

        for (size_t j = i; this->row_size > j; j++)
            out[i][j] = copy[0][j - i];

        try
        {
            copy.removeColumn(0);
            copy.removeRow(0);
            out.appendRow();
        }
        catch (const ErrorMatrixEmpty &er)
        {
        }

        i++;
        k = 0;
    }
    while (this->size > i);

    this->data = out.data;

    return swaps;
}

template <typename Type>
std::shared_ptr<MatrixRow<Type>[]> Matrix<Type>::allocate_matrix(const size_t size_row,
                                                                 const size_t size_column)
{
    if (0 == size_row)
        throw ErrorMatrixEmptyAllocation(__FILE__, __LINE__, __FUNCTION__);

    try
    {
        std::shared_ptr<MatrixRow<Type>[]> out = nullptr;
        out.reset(new MatrixRow<Type>[size_row]);

        if (0 != size_column)
            for (size_t i = 0; size_row > i; i++)
                out[i] = MatrixRow<Type>(size_column);

        return out;
    }
    catch (std::bad_alloc &err)
    {
        throw ErrorMatrixAllocation(__FILE__, __LINE__, __FUNCTION__);
    }
}

template <typename Type>
std::shared_ptr<MatrixRow<Type>[]> Matrix<Type>::allocate_copy(const std::shared_ptr<MatrixRow<Type>[]> ptr,
                                                               const size_t size_row,
                                                               const size_t size_column)
{
    if (0 == size_row || 0 == size_column)
        throw ErrorMatrixEmptyAllocation(__FILE__, __LINE__, __FUNCTION__);

    if (nullptr == ptr)
        throw ErrorMatrixNullPointer(__FILE__, __LINE__, __FUNCTION__);

    try
    {
        std::shared_ptr<MatrixRow<Type>[]> out = nullptr;
        out.reset(new MatrixRow<Type>[size_row]);

        for (size_t i = 0; size_row > i; i++)
            out[i] = MatrixRow<Type>(ptr[i]);

        return out;
    }
    catch (std::bad_alloc &err)
    {
        throw ErrorMatrixAllocation(__FILE__, __LINE__, __FUNCTION__);
    }
}

template <typename Type>
std::ostream &operator << (std::ostream &stream, const Matrix<Type> &matrix)
{
    for (const MatrixRow<Type> &row : matrix)
        stream << row << std::endl;

    return stream;
}

template <typename Type>
Matrix<Type> operator + (const Type &value, const Matrix<Type> &matrix)
{
    return matrix + value;
}

template <typename Type>
Matrix<Type> operator - (const Type &value, const Matrix<Type> &matrix)
{
    return matrix - value;
}

template <typename Type>
Matrix<Type> operator * (const Type &value, const Matrix<Type> &matrix)
{
    return matrix * value;
}

template <typename Type>
Type find_min(const Matrix<Type> &matrix)
{
    Type min = find_min(matrix[0]), val;

    for (MatrixRow<Type> &row : matrix)
    {
        val = find_min(row);

        if (min > val)
            min = val;
    }

    return min;
}

template <typename Type>
Type find_max(const Matrix<Type> &matrix)
{
    Type max = find_max(matrix[0]), val;

    for (MatrixRow<Type> &row : matrix)
    {
        val = find_max(row);

        if (max < val)
            max = val;
    }

    return max;
}

template <typename Type>
Type find_sum(const Matrix<Type> &matrix)
{
    Type result = Type();

    for (MatrixRow<Type> &row : matrix)
        result += find_sum(row);

    return result;
}

#endif

