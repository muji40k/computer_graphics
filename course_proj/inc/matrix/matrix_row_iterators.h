#ifndef _MATRIX_ROW_ITERATORS_H_
#define _MATRIX_ROW_ITERATORS_H_

#include <memory>
#include "matrix_row.h"

#define MIN_INDEX 1

template <typename Type>
class MatrixRowIterator
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Type;
        using difference_type = Type;
        using pointer = Type *;
        using reference = Type &;

    public:
        MatrixRowIterator(void) = default;
        explicit MatrixRowIterator(MatrixRow<Type> &row);
        MatrixRowIterator(const MatrixRowIterator<Type> &iter);
        MatrixRowIterator(MatrixRowIterator<Type> &&iter);
        ~MatrixRowIterator(void) = default;

        MatrixRowIterator<Type> &operator = (const MatrixRowIterator<Type> &iter);
        MatrixRowIterator<Type> &operator = (MatrixRow<Type> &row);

        operator bool(void) const;
        bool isExpired(void) const;

        Type &operator * (void);
        Type &get(void);

        MatrixRowIterator<Type> &operator ++ (void);
        MatrixRowIterator<Type> operator  ++ (int);
        MatrixRowIterator<Type> &operator -- (void);
        MatrixRowIterator<Type> operator  -- (int);
        MatrixRowIterator<Type> &operator += (const size_t offset);
        MatrixRowIterator<Type> &operator -= (const size_t offset);

        MatrixRowIterator<Type> operator + (const size_t offset) const;
        MatrixRowIterator<Type> operator - (const size_t offset) const;

        int compare(const MatrixRowIterator<Type> &iter) const;

        bool operator == (const MatrixRowIterator<Type> &iter) const;
        bool operator != (const MatrixRowIterator<Type> &iter) const;
        bool operator >= (const MatrixRowIterator<Type> &iter) const;
        bool operator <= (const MatrixRowIterator<Type> &iter) const;
        bool operator >  (const MatrixRowIterator<Type> &iter) const;
        bool operator <  (const MatrixRowIterator<Type> &iter) const;

    protected:
        void set_ptr(const std::weak_ptr<Type[]> &ptr);
        void set_index(const size_t index);
        void set_size(const size_t size);
        void set_iter(const MatrixRowIterator<Type> &iter);

    private:
        std::weak_ptr<Type[]> ptr;
        size_t index = MIN_INDEX;
        size_t size = MIN_INDEX;
};

template <typename Type>
class ConstMatrixRowIterator : public MatrixRowIterator<Type>
{
    public:
        ConstMatrixRowIterator(void) = default;
        explicit ConstMatrixRowIterator(const MatrixRow<Type> &row);
        ConstMatrixRowIterator(const ConstMatrixRowIterator<Type> &iter);
        ConstMatrixRowIterator(ConstMatrixRowIterator<Type> &&iter);
        ~ConstMatrixRowIterator(void) = default;

        ConstMatrixRowIterator<Type> &operator = (const ConstMatrixRowIterator<Type> &iter);
        ConstMatrixRowIterator<Type> &operator = (const MatrixRow<Type> &row);

        const Type &operator * (void);
        const Type &get(void);

        ConstMatrixRowIterator<Type> &operator ++ (void);
        ConstMatrixRowIterator<Type> operator  ++ (int);
        ConstMatrixRowIterator<Type> &operator -- (void);
        ConstMatrixRowIterator<Type> operator  -- (int);
        ConstMatrixRowIterator<Type> &operator += (const size_t offset);
        ConstMatrixRowIterator<Type> &operator -= (const size_t offset);

        ConstMatrixRowIterator<Type> operator + (const size_t offset) const;
        ConstMatrixRowIterator<Type> operator - (const size_t offset) const;
};

template <typename Type>
class ReverseMatrixRowIterator : public MatrixRowIterator<Type>
{
    public:
        ReverseMatrixRowIterator(void) = default;
        explicit ReverseMatrixRowIterator(MatrixRow<Type> &row);
        ReverseMatrixRowIterator(const ReverseMatrixRowIterator<Type> &iter);
        ReverseMatrixRowIterator(ReverseMatrixRowIterator<Type> &&iter);
        ~ReverseMatrixRowIterator(void) = default;

        ReverseMatrixRowIterator<Type> &operator = (const ReverseMatrixRowIterator<Type> &iter);
        ReverseMatrixRowIterator<Type> &operator = (MatrixRow<Type> &row);

        Type &operator * (void);
        Type &get(void);

        ReverseMatrixRowIterator<Type> &operator ++ (void);
        ReverseMatrixRowIterator<Type> operator  ++ (int);
        ReverseMatrixRowIterator<Type> &operator -- (void);
        ReverseMatrixRowIterator<Type> operator  -- (int);
        ReverseMatrixRowIterator<Type> &operator += (const size_t offset);
        ReverseMatrixRowIterator<Type> &operator -= (const size_t offset);

        ReverseMatrixRowIterator<Type> operator + (const size_t offset) const;
        ReverseMatrixRowIterator<Type> operator - (const size_t offset) const;

        bool operator >= (const ReverseMatrixRowIterator<Type> &iter) const;
        bool operator <= (const ReverseMatrixRowIterator<Type> &iter) const;
        bool operator >  (const ReverseMatrixRowIterator<Type> &iter) const;
        bool operator <  (const ReverseMatrixRowIterator<Type> &iter) const;
};

template <typename Type>
class ConstReverseMatrixRowIterator : public ReverseMatrixRowIterator<Type>
{
    public:
        ConstReverseMatrixRowIterator(void) = default;
        explicit ConstReverseMatrixRowIterator(const MatrixRow<Type> &row);
        ConstReverseMatrixRowIterator(const ConstReverseMatrixRowIterator<Type> &iter);
        ConstReverseMatrixRowIterator(ConstReverseMatrixRowIterator<Type> &&iter);
        ~ConstReverseMatrixRowIterator(void) = default;

        ConstReverseMatrixRowIterator<Type> &operator = (const ConstReverseMatrixRowIterator<Type> &iter);
        ConstReverseMatrixRowIterator<Type> &operator = (const MatrixRow<Type> &row);

        const Type &operator * (void);
        const Type &get(void);

        ConstReverseMatrixRowIterator<Type> &operator ++ (void);
        ConstReverseMatrixRowIterator<Type> operator  ++ (int);
        ConstReverseMatrixRowIterator<Type> &operator -- (void);
        ConstReverseMatrixRowIterator<Type> operator  -- (int);
        ConstReverseMatrixRowIterator<Type> &operator += (const size_t offset);
        ConstReverseMatrixRowIterator<Type> &operator -= (const size_t offset);

        ConstReverseMatrixRowIterator<Type> operator + (const size_t offset) const;
        ConstReverseMatrixRowIterator<Type> operator - (const size_t offset) const;
};

#include "matrix_row_iterators.hpp"
#undef MIN_INDEX

#endif

