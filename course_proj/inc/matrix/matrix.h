#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>
#include <memory>
#include <initializer_list>
#include <iostream>

template <typename Type>
class Matrix;

#include "matrix_row.h"
#include "base_container.h"
#include "matrix_iterators.h"

using namespace std;

template <typename Type>
using const_initializer_matrix = \
const initializer_list<const initializer_list<Type>>;

template <typename Type>
std::ostream &operator << (std::ostream &stream, const Matrix<Type> &matrix);

template <typename Type>
class Matrix : public BaseContainer
{
    friend MatrixIterator<Type>::MatrixIterator(Matrix<Type> &matrix);
    friend MatrixIterator<Type> &MatrixIterator<Type>::operator = (Matrix<Type> &matrix);

    friend ConstMatrixIterator<Type>::ConstMatrixIterator(const Matrix<Type> &matrix);
    friend ConstMatrixIterator<Type> &ConstMatrixIterator<Type>::operator = (const Matrix<Type> &matrix);

    friend ReverseMatrixIterator<Type>::ReverseMatrixIterator(Matrix<Type> &matrix);
    friend ReverseMatrixIterator<Type> &ReverseMatrixIterator<Type>::operator = (Matrix<Type> &matrix);

    friend ConstReverseMatrixIterator<Type>::ConstReverseMatrixIterator(const Matrix<Type> &matrix);
    friend ConstReverseMatrixIterator<Type> &ConstReverseMatrixIterator<Type>::operator = (const Matrix<Type> &matrix);

    friend std::ostream &operator << <Type>(std::ostream &, const Matrix<Type> &);

    public:
        Matrix(void);
        Matrix(const Matrix<Type> &matrix);
        Matrix(Matrix<Type> &&matrix);

        Matrix(const size_t rows, const size_t columns,
               const Type &value = Type());
        explicit Matrix(const_initializer_matrix<Type> matrix);
        Matrix(const Type **matrix, const size_t rows, const size_t columns);

        template <typename Iter>
        Matrix(const Iter begin, const Iter end);

        Matrix<Type> &operator = (const Matrix<Type> &matrix);
        Matrix<Type> &operator = (const_initializer_matrix<Type> matrix);

        ~Matrix(void) = default;

        size_t getRows(void);
        size_t getColumns(void);

        operator bool(void) const;
        bool isEmpty(void)  const override;

        MatrixRow<Type> &getRow(const size_t index);
        MatrixRow<Type> &operator [] (const size_t index);

        const MatrixRow<Type> &getRow(const size_t index) const;
        const MatrixRow<Type> &operator [] (const size_t index) const;

        Matrix<Type> &fill(const Type &value = Type());
        Matrix<Type> copy(void);

        Matrix<Type> &swapColumns(const size_t column1, const size_t column2);
        Matrix<Type> &swapRows(const size_t row1, const size_t row2);

        Matrix<Type> &insertRow(const size_t index,
                                const shared_ptr<Type[]> row,
                                const size_t size);
        Matrix<Type> &insertRow(const size_t index,
                                const initializer_list<Type> row);
        Matrix<Type> &insertRow(const size_t index, const MatrixRow<Type> &row);
        Matrix<Type> &insertRow(const size_t index, const Type &value = Type());
        Matrix<Type> &insertColumn(const size_t index,
                                   const shared_ptr<Type[]> column,
                                   const size_t size);
        Matrix<Type> &insertColumn(const size_t index,
                                   const initializer_list<Type> column);
        Matrix<Type> &insertColumn(const size_t index,
                                   const Type &value = Type());

        Matrix<Type> &appendRow(const shared_ptr<Type[]> row,
                                const size_t size);
        Matrix<Type> &appendRow(const initializer_list<Type> row);
        Matrix<Type> &appendRow(const MatrixRow<Type> &row);
        Matrix<Type> &appendRow(const Type &value = Type());
        Matrix<Type> &appendColumn(const shared_ptr<Type[]> column,
                                   const size_t size);
        Matrix<Type> &appendColumn(const initializer_list<Type> column);
        Matrix<Type> &appendColumn(const Type &value = Type());

        Matrix<Type> &removeColumn(const size_t index);
        Matrix<Type> &removeRow(const size_t index);

        Matrix<Type> &sortColumns(int (&compare)(const Type &, const Type &));
        Matrix<Type> &sortRows(int (&compare)(const Type &, const Type &));
        Matrix<Type> &sortByColumn(const size_t index,
                                   int (&compare)(const Type &, const Type &));
        Matrix<Type> &sortByRow(const size_t index,
                                int (&compare)(const Type &, const Type &));

        Matrix<Type> sortedColumns(int (&compare)(const Type &, const Type &))
                     const;
        Matrix<Type> sortedRows(int (&compare)(const Type &, const Type &))
                     const;
        Matrix<Type> sortedByColumn(const size_t index,
                                    int (&compare)(const Type &, const Type &))
                     const;
        Matrix<Type> sortedByRow(const size_t index,
                                 int (&compare)(const Type &, const Type &))
                     const;

        bool isEqual(const Matrix<Type> &matrix)       const;
        bool operator == (const Matrix<Type> &matrix) const;
        bool operator != (const Matrix<Type> &matrix) const;

        Matrix<Type> operator + (const Matrix<Type> &matrix) const;
        Matrix<Type> operator + (const Type data)            const;
        Matrix<Type> operator - (const Matrix<Type> &matrix) const;
        Matrix<Type> operator - (const Type data)            const;
        Matrix<Type> operator * (const Matrix<Type> &matrix) const;
        Matrix<Type> operator * (const Type data)            const;
        Matrix<Type> operator / (const Type data)            const;

        Matrix<Type> &operator += (const Matrix<Type> &matrix);
        Matrix<Type> &operator += (const Type data);
        Matrix<Type> &operator -= (const Matrix<Type> &matrix);
        Matrix<Type> &operator -= (const Type data);
        Matrix<Type> &operator *= (const Matrix<Type> &matrix);
        Matrix<Type> &operator *= (const Type data);
        Matrix<Type> &operator /= (const Type data);

        Matrix<Type> getTransposed(void) const;
        Matrix<Type> getInversed(void)   const;

        Matrix<Type> &transpose(void);
        Matrix<Type> &inverse(void);

        Type determinant(void) const;
        std::shared_ptr<Type[]> solveLinearSystem(void) const;

        MatrixIterator<Type> begin(void);
        MatrixIterator<Type> end(void);

        ConstMatrixIterator<Type> begin(void) const;
        ConstMatrixIterator<Type> end(void)   const;

        ConstMatrixIterator<Type> cbegin(void);
        ConstMatrixIterator<Type> cend(void);

        ReverseMatrixIterator<Type> rbegin(void);
        ReverseMatrixIterator<Type> rend(void);

        ConstReverseMatrixIterator<Type> crbegin(void);
        ConstReverseMatrixIterator<Type> crend(void);

    private:
        shared_ptr<MatrixRow<Type>[]> data;
        size_t row_size;

        size_t descendingGauss(void);

        static std::shared_ptr<MatrixRow<Type>[]> allocate_matrix(const size_t size_row,
                                                                  const size_t size_column);
        static std::shared_ptr<MatrixRow<Type>[]> allocate_copy(const std::shared_ptr<MatrixRow<Type>[]> ptr,
                                                                const size_t size_row,
                                                                const size_t size_column);
};

template <typename Type>
Matrix<Type> operator + (const Type &value, const Matrix<Type> &matrix);

template <typename Type>
Matrix<Type> operator - (const Type &value, const Matrix<Type> &matrix);

template <typename Type>
Matrix<Type> operator * (const Type &value, const Matrix<Type> &matrix);

template <typename Type>
Type find_min(const Matrix<Type> &matrix);

template <typename Type>
Type find_max(const Matrix<Type> &matrix);

template <typename Type>
Type find_sum(const Matrix<Type> &matrix);

#include "matrix.hpp"

#endif

