#ifndef _MATRIX_ITERATORS_H_
#define _MATRIX_ITERATORS_H_

#include <memory>
#include "matrix.h"

#define MIN_INDEX 1

template <typename Type>
class MatrixIterator
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = MatrixRow<Type>;
        using difference_type = MatrixRow<Type>;
        using pointer = MatrixRow<Type> *;
        using reference = MatrixRow<Type> &;

    public:
        MatrixIterator(void) = default;
        explicit MatrixIterator(Matrix<Type> &matrix);
        MatrixIterator(const MatrixIterator<Type> &iter);
        MatrixIterator(MatrixIterator<Type> &&iter);
        ~MatrixIterator(void) = default;

        MatrixIterator<Type> &operator = (const MatrixIterator<Type> &iter);
        MatrixIterator<Type> &operator = (Matrix<Type> &matrix);

        operator bool(void) const;
        bool isExpired(void) const;

        MatrixRow<Type> &operator * (void);
        MatrixRow<Type> &get(void);

        MatrixIterator<Type> &operator ++ (void);
        MatrixIterator<Type> operator  ++ (int);
        MatrixIterator<Type> &operator -- (void);
        MatrixIterator<Type> operator  -- (int);
        MatrixIterator<Type> &operator += (const size_t offset);
        MatrixIterator<Type> &operator -= (const size_t offset);

        MatrixIterator<Type> operator + (const size_t offset) const;
        MatrixIterator<Type> operator - (const size_t offset) const;

        int compare(const MatrixIterator<Type> &iter) const;

        bool operator == (const MatrixIterator<Type> &iter) const;
        bool operator != (const MatrixIterator<Type> &iter) const;
        bool operator >= (const MatrixIterator<Type> &iter) const;
        bool operator <= (const MatrixIterator<Type> &iter) const;
        bool operator >  (const MatrixIterator<Type> &iter) const;
        bool operator <  (const MatrixIterator<Type> &iter) const;

    protected:
        void set_ptr(const std::weak_ptr<MatrixRow<Type>[]> &ptr);
        void set_index(const size_t index);
        void set_size(const size_t size);
        void set_iter(const MatrixIterator<Type> &iter);

    private:
        std::weak_ptr<MatrixRow<Type>[]> ptr;
        size_t index = MIN_INDEX;
        size_t size = MIN_INDEX;
};

template <typename Type>
class ConstMatrixIterator : public MatrixIterator<Type>
{
    public:
        ConstMatrixIterator(void) = default;
        explicit ConstMatrixIterator(const Matrix<Type> &matrix);
        ConstMatrixIterator(const ConstMatrixIterator<Type> &iter);
        ConstMatrixIterator(ConstMatrixIterator<Type> &&iter);
        ~ConstMatrixIterator(void) = default;

        ConstMatrixIterator<Type> &operator = (const ConstMatrixIterator<Type> &iter);
        ConstMatrixIterator<Type> &operator = (const Matrix<Type> &matrix);

        const MatrixRow<Type> &operator * (void);
        const MatrixRow<Type> &get(void);

        ConstMatrixIterator<Type> &operator ++ (void);
        ConstMatrixIterator<Type> operator  ++ (int);
        ConstMatrixIterator<Type> &operator -- (void);
        ConstMatrixIterator<Type> operator  -- (int);
        ConstMatrixIterator<Type> &operator += (const size_t offset);
        ConstMatrixIterator<Type> &operator -= (const size_t offset);

        ConstMatrixIterator<Type> operator + (const size_t offset) const;
        ConstMatrixIterator<Type> operator - (const size_t offset) const;
};

template <typename Type>
class ReverseMatrixIterator : public MatrixIterator<Type>
{
    public:
        ReverseMatrixIterator(void) = default;
        explicit ReverseMatrixIterator(Matrix<Type> &matrix);
        ReverseMatrixIterator(const ReverseMatrixIterator<Type> &iter);
        ReverseMatrixIterator(ReverseMatrixIterator<Type> &&iter);
        ~ReverseMatrixIterator(void) = default;

        ReverseMatrixIterator<Type> &operator = (const ReverseMatrixIterator<Type> &iter);
        ReverseMatrixIterator<Type> &operator = (Matrix<Type> &matrix);

        MatrixRow<Type> &operator * (void);
        MatrixRow<Type> &get(void);

        ReverseMatrixIterator<Type> &operator ++ (void);
        ReverseMatrixIterator<Type> operator  ++ (int);
        ReverseMatrixIterator<Type> &operator -- (void);
        ReverseMatrixIterator<Type> operator  -- (int);
        ReverseMatrixIterator<Type> &operator += (const size_t offset);
        ReverseMatrixIterator<Type> &operator -= (const size_t offset);

        ReverseMatrixIterator<Type> operator + (const size_t offset) const;
        ReverseMatrixIterator<Type> operator - (const size_t offset) const;

        bool operator >= (const ReverseMatrixIterator<Type> &iter) const;
        bool operator <= (const ReverseMatrixIterator<Type> &iter) const;
        bool operator >  (const ReverseMatrixIterator<Type> &iter) const;
        bool operator <  (const ReverseMatrixIterator<Type> &iter) const;
};

template <typename Type>
class ConstReverseMatrixIterator : public ReverseMatrixIterator<Type>
{
    public:
        ConstReverseMatrixIterator(void) = default;
        explicit ConstReverseMatrixIterator(const Matrix<Type> &matrix);
        ConstReverseMatrixIterator(const ConstReverseMatrixIterator<Type> &iter);
        ConstReverseMatrixIterator(ConstReverseMatrixIterator<Type> &&iter);
        ~ConstReverseMatrixIterator(void) = default;

        ConstReverseMatrixIterator<Type> &operator = (const ConstReverseMatrixIterator<Type> &iter);
        ConstReverseMatrixIterator<Type> &operator = (const Matrix<Type> &matrix);

        const MatrixRow<Type> &operator * (void);
        const MatrixRow<Type> &get(void);

        ConstReverseMatrixIterator<Type> &operator ++ (void);
        ConstReverseMatrixIterator<Type> operator  ++ (int);
        ConstReverseMatrixIterator<Type> &operator -- (void);
        ConstReverseMatrixIterator<Type> operator  -- (int);
        ConstReverseMatrixIterator<Type> &operator += (const size_t offset);
        ConstReverseMatrixIterator<Type> &operator -= (const size_t offset);

        ConstReverseMatrixIterator<Type> operator + (const size_t offset) const;
        ConstReverseMatrixIterator<Type> operator - (const size_t offset) const;
};

#include "matrix_iterators.hpp"
#undef MIN_INDEX

#endif

