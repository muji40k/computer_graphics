#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <cstdlib>
#include <initializer_list>
#include <iostream>

#include "matrix.h"

template <typename Type, size_t nDim = 3>
class Transform;

template <typename Type, size_t nDim = 3>
class Transformable
{
    public:
        virtual ~Transformable(void) = 0;
        virtual void apply(const Transform<Type, nDim> &transform) = 0;
        virtual void undo(const Transform<Type, nDim> &transform) = 0;
};

template <typename Type, size_t nDim>
Transformable<Type, nDim>::~Transformable(void) {}

template <typename Type, size_t nDim = 3>
class BaseTransformStrategy
{
    public:
        BaseTransformStrategy(void);

        const Matrix<Type> &getMatrix(void) const;
        const Matrix<Type> &getInverse(void) const;

    protected:
        Matrix<Type> matrix;
        Matrix<Type> inverse;
};

template <typename Type, size_t nDim>
class Transform
{
    public:
        Transform(void);
        Transform(const Transform<Type, nDim> &transform);
        Transform(Transform<Type, nDim> &&transform);

        void accept(const BaseTransformStrategy<Type, nDim> &strategy);

        const Matrix<Type> &getMatrix(void) const;
        const Matrix<Type> &getInverse(void) const;

        Transform<Type, nDim> operator + (const Transform<Type, nDim> &trans) const;

        Transform<Type, nDim> &operator = (const Transform<Type, nDim> &trans);
        Transform<Type, nDim> &operator += (const Transform<Type, nDim> &trans);

        Transform<Type, nDim> &inverse(void);
        Transform<Type, nDim> inversed(void) const;

    private:
        Matrix<Type> matrix_forward;
        Matrix<Type> matrix_inverse;
};

template <typename Type, size_t nDim = 3>
std::ostream &operator << (std::ostream &stream, const Transform<Type, nDim> &trans);

#include "transform.hpp"

#endif

