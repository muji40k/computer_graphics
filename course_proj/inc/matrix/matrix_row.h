#ifndef _MATRIX_ROW_H_
#define _MATRIX_ROW_H_

template <typename Type>
class MatrixRow;

#include <cstdlib>
#include <memory>

#include "base_container.h"
#include "matrix_row_iterators.h"

template <typename Type>
std::ostream &operator << (std::ostream &stream, const MatrixRow<Type> &row);

template <typename Type>
class MatrixRow : public BaseContainer
{
    friend MatrixRowIterator<Type>::MatrixRowIterator(MatrixRow<Type> &row);
    friend MatrixRowIterator<Type> &MatrixRowIterator<Type>::operator = (MatrixRow<Type> &row);

    friend ConstMatrixRowIterator<Type>::ConstMatrixRowIterator(const MatrixRow<Type> &row);
    friend ConstMatrixRowIterator<Type> &ConstMatrixRowIterator<Type>::operator = (const MatrixRow<Type> &row);

    friend ReverseMatrixRowIterator<Type>::ReverseMatrixRowIterator(MatrixRow<Type> &row);
    friend ReverseMatrixRowIterator<Type> &ReverseMatrixRowIterator<Type>::operator = (MatrixRow<Type> &row);

    friend ConstReverseMatrixRowIterator<Type>::ConstReverseMatrixRowIterator(const MatrixRow<Type> &row);
    friend ConstReverseMatrixRowIterator<Type> &ConstReverseMatrixRowIterator<Type>::operator = (const MatrixRow<Type> &row);

    friend std::ostream &operator << <Type>(std::ostream &, const MatrixRow<Type> &);

    public:
        MatrixRow(void);
        MatrixRow(const MatrixRow<Type> &row);
        MatrixRow(MatrixRow<Type> &&row);

        MatrixRow(std::shared_ptr<Type[]> row, const size_t size);
        MatrixRow(const size_t size, const Type &value = Type());
        explicit MatrixRow(const std::initializer_list<Type> array);
        MatrixRow(const Type *array, const size_t size);

        template <typename Iter>
        MatrixRow(const Iter start, const Iter end);

        ~MatrixRow(void) = default;

        MatrixRow<Type> &operator = (const MatrixRow<Type> &row);
        MatrixRow<Type> &operator = (const std::initializer_list<Type> array);

        operator bool(void) const;
        bool isEmpty(void)  const override;

        Type &get(const size_t index);
        Type &operator [] (const size_t index);

        const Type &get(const size_t index) const;
        const Type &operator [] (const size_t index) const;

        MatrixRow<Type> copy(void);
        MatrixRow<Type> &fill(const Type &value = Type());

        MatrixRow<Type> &swap(const size_t column1, const size_t column2);
        MatrixRow<Type> &insert(const Type &data, const size_t index);
        MatrixRow<Type> &append(const Type &data = Type());

        MatrixRow<Type> &remove(const size_t index);

        MatrixRow<Type> &sort(int (&compare)(const Type &, const Type &));
        MatrixRow<Type> sorted(int (&compare)(const Type &, const Type &))
                        const;

        bool isEqual(const MatrixRow<Type> &row)       const;
        bool operator == (const MatrixRow<Type> &row) const;
        bool operator != (const MatrixRow<Type> &row) const;

        MatrixRow<Type> operator + (const MatrixRow<Type> &row) const;
        MatrixRow<Type> operator + (const Type &data)           const;
        MatrixRow<Type> operator - (const MatrixRow<Type> &row) const;
        MatrixRow<Type> operator - (const Type &data)           const;
        MatrixRow<Type> operator * (const Type &data)           const;
        MatrixRow<Type> operator / (const Type &data)           const;

        MatrixRow<Type> &operator += (const MatrixRow<Type> &row);
        MatrixRow<Type> &operator += (const Type &data);
        MatrixRow<Type> &operator -= (const MatrixRow<Type> &row);
        MatrixRow<Type> &operator -= (const Type &data);
        MatrixRow<Type> &operator *= (const Type &data);
        MatrixRow<Type> &operator /= (const Type &data);

        MatrixRowIterator<Type> begin(void);
        MatrixRowIterator<Type> end(void);

        ConstMatrixRowIterator<Type> begin(void) const;
        ConstMatrixRowIterator<Type> end(void)   const;

        ConstMatrixRowIterator<Type> cbegin(void);
        ConstMatrixRowIterator<Type> cend(void);

        ReverseMatrixRowIterator<Type> rbegin(void);
        ReverseMatrixRowIterator<Type> rend(void);

        ConstReverseMatrixRowIterator<Type> crbegin(void);
        ConstReverseMatrixRowIterator<Type> crend(void);

    private:
        std::shared_ptr<Type[]> data = nullptr;

        static std::shared_ptr<Type[]> allocate_row(const size_t size);
        static std::shared_ptr<Type[]> allocate_copy(const std::shared_ptr<Type[]> ptr,
                                                     const size_t size);

};

template <typename Type>
MatrixRow<Type> operator + (const Type &value, const MatrixRow<Type> &row);

template <typename Type>
MatrixRow<Type> operator - (const Type &value, const MatrixRow<Type> &row);

template <typename Type>
MatrixRow<Type> operator * (const Type &value, const MatrixRow<Type> &row);

template <typename Type>
Type find_min(const MatrixRow<Type> &row);

template <typename Type>
Type find_max(const MatrixRow<Type> &row);

template <typename Type>
Type find_sum(const MatrixRow<Type> &row);

#include "matrix_row.hpp"

#endif

