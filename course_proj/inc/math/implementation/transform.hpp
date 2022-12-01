#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "transform.h"

template <typename Type, size_t nDim>
BaseTransformStrategy<Type, nDim>::BaseTransformStrategy(void)
    : matrix(Matrix<Type>(nDim + 1, nDim + 1)),
      inverse(Matrix<Type>(nDim + 1, nDim + 1))
{
    for (size_t i = 0; nDim >= i; i++)
    {
        this->matrix[i][i] = Type(1);
        this->inverse[i][i] = Type(1);
    }
}

template <typename Type, size_t nDim>
const Matrix<Type> &BaseTransformStrategy<Type, nDim>::getMatrix(void) const
{
    return this->matrix;
}

template <typename Type, size_t nDim>
const Matrix<Type> &BaseTransformStrategy<Type, nDim>::getInverse(void) const
{
    return this->inverse;
}

template <typename Type, size_t nDim>
Transform<Type, nDim>::Transform(void)
    : matrix_forward(Matrix<Type>(nDim + 1, nDim + 1)),
      matrix_inverse(Matrix<Type>(nDim + 1, nDim + 1))
{
    for (size_t i = 0; nDim >= i; i++)
    {
        this->matrix_forward[i][i] = Type(1);
        this->matrix_inverse[i][i] = Type(1);
    }
}

template <typename Type, size_t nDim>
Transform<Type, nDim>::Transform(const Transform<Type, nDim> &transform)
{
    this->matrix_forward = transform.matrix_forward;
    this->matrix_inverse = transform.matrix_inverse;
}

template <typename Type, size_t nDim>
Transform<Type, nDim>::Transform(Transform<Type, nDim> &&transform)
{
    this->matrix_forward = transform.matrix_forward;
    this->matrix_inverse = transform.matrix_inverse;
}

template <typename Type, size_t nDim>
void Transform<Type, nDim>::accept(const BaseTransformStrategy<Type, nDim> &strategy)
{
    this->matrix_forward *= strategy.getMatrix();
    this->matrix_inverse = strategy.getInverse() * this->matrix_inverse;
}

template <typename Type, size_t nDim>
const Matrix<Type> &Transform<Type, nDim>::getMatrix(void) const
{
    return this->matrix_forward;
}

template <typename Type, size_t nDim>
const Matrix<Type> &Transform<Type, nDim>::getInverse(void) const
{
    return this->matrix_inverse;
}

template <typename Type, size_t nDim>
Transform<Type, nDim> Transform<Type, nDim>::operator + (const Transform<Type, nDim> &trans) const
{
    Transform<Type, nDim> out (*this);

    return out += trans;
}

template <typename Type, size_t nDim>
Transform<Type, nDim> &Transform<Type, nDim>::operator = (const Transform<Type, nDim> &trans)
{
    this->matrix_forward = trans.matrix_forward;
    this->matrix_inverse = trans.matrix_inverse;

    return *this;
}

template <typename Type, size_t nDim>
Transform<Type, nDim> &Transform<Type, nDim>::operator += (const Transform<Type, nDim> &trans)
{
    this->matrix_forward *= trans.matrix_forward;
    this->matrix_inverse = trans.matrix_inverse * this->matrix_inverse;

    return *this;
}

template <typename Type, size_t nDim>
Transform<Type, nDim> &Transform<Type, nDim>::inverse(void)
{
    Matrix<Type> tmp = this->matrix_forward;
    this->matrix_forward = this->matrix_inverse;
    this->matrix_inverse = tmp;

    return *this;
}

template <typename Type, size_t nDim>
Transform<Type, nDim> Transform<Type, nDim>::inversed(void) const
{
    Transform<Type, nDim> out(*this);
    out.inverse();

    return out;
}

template <typename Type, size_t nDim>
std::ostream &operator << (std::ostream &stream, const Transform<Type, nDim> &trans)
{
    stream << "Transform:" << std::endl \
           << "\tMatrix:" << std::endl << trans.getMatrix()
           << "\tInverse:" << std::endl << trans.getInverse();

    return stream;
}

#endif

