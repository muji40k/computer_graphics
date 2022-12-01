#ifndef _BASIS_HPP_
#define _BASIS_HPP_

#include "basis.h"

#include <cmath>
#include <iterator>

#include "matrix.h"

template <typename Type, size_t nDim>
Basis<Type, nDim>::Basis(void)
{
    for (size_t i = 0; nDim > i; i++)
        this->_axis[i][i] = Type(1);
}

template <typename Type, size_t nDim>
template <size_t oDim>
Basis<Type, nDim>::Basis(const Basis<Type, oDim> &basis) : Basis<Type, nDim>()
{
    this->_center = basis._center;
    const size_t limit = (nDim < oDim) ? nDim : oDim;

    for (size_t i = 0; limit > i; i++)
        this->_axis[i] = basis._axis[i];

    this->orthogonalize();
}

template <typename Type, size_t nDim>
template <size_t oDim>
Basis<Type, nDim>::Basis(Basis<Type, oDim> &&basis) : Basis<Type, nDim>()
{
    this->_center = basis._center;
    const size_t limit = (nDim < oDim) ? nDim : oDim;

    for (size_t i = 0; limit > i; i++)
        this->_axis[i] = basis._axis[i];

    this->orthogonalize();
}

template <typename Type, size_t nDim>
Basis<Type, nDim>::Basis(const std::initializer_list<const Vector<Type, nDim>> &list,
                         const Point<Type, nDim> &center)
    : Basis<Type, nDim>()
{
    this->_center = center;
    size_t limit = nDim;
    auto it = list.begin();

    if (list.size() < limit)
        limit = nDim;

    for (size_t i = 0; limit > i; i++, it++)
        this->_axis[i] = *it;

    if (Basis<Type, nDim>::isDegenerate(this->_axis))
        throw CALL_EX(DegenrateBasisException);

    this->orthogonalize();
}

template <typename Type, size_t nDim>
template <size_t oDim>
Basis<Type, nDim> &Basis<Type, nDim>::operator = (const Basis<Type, oDim> &basis)
{
    this->_center = basis._center;
    const size_t limit = (nDim < oDim) ? nDim : oDim;

    for (size_t i = 0; limit > i; i++)
        this->_axis[i] = basis._axis[i];

    this->orthogonalize();

    return *this;
}

template <typename Type, size_t nDim>
bool Basis<Type, nDim>::operator == (const Basis<Type, nDim> &basis)
{
    bool mark = basis._center == this->_center;

    for (size_t i = 0; mark && nDim > i; i++)
        mark = basis._axis[i] == this->_axis[i];

    return mark;
}

template <typename Type, size_t nDim>
bool Basis<Type, nDim>::operator != (const Basis<Type, nDim> &basis)
{
    return !(*this == basis);
}

template <typename Type, size_t nDim>
void Basis<Type, nDim>::setCenter(const Point<Type, nDim> &point)
{
    this->_center = point;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Basis<Type, nDim>::getCenter(void) const
{
    return this->_center;
}

template <typename Type, size_t nDim>
template <size_t oDim>
void Basis<Type, nDim>::setVector(const Vector<Type, oDim> &vector, const size_t index)
{
    if (nDim <= index)
        throw CALL_EX(IndexViolationBasisException);

    Vector<Type, nDim> tmp[nDim];

    for (size_t i = 0; nDim > i; i++)
        tmp[i] = this->_axis[i];

    tmp[index] = vector;

    if (Basis<Type, nDim>::isDegenerate(tmp))
        throw CALL_EX(DegenrateBasisException);

    for (size_t i = 0; nDim > i; i++)
        this->_axis[i] = tmp[i];

    this->orthogonalize();
}

template <typename Type, size_t nDim>
Vector<Type, nDim> Basis<Type, nDim>::getVector(const size_t index) const
{
    if (nDim <= index)
        throw CALL_EX(IndexViolationBasisException);

    return this->_axis[index];
}

template <typename Type, size_t nDim>
bool Basis<Type, nDim>::isDegenerate(const Vector<Type, nDim>(&arr)[nDim])
{
    for (size_t i = 0; nDim > i; i++)
        if (arr[i])
            return true;

    Matrix<Type> matrix(nDim, nDim);

    for (size_t i = 0; nDim > i; i++)
        for (size_t j = 0; nDim > j; j++)
            matrix[i][j] = arr[i][j];

    if (EPS > fabs(double(matrix.determinant())))
        return true;

    return false;
}

template <typename Type, size_t nDim>
void Basis<Type, nDim>::orthogonalize(void)
{
    Basis<Type, nDim>::_orthogonalize(this->_axis);
}

template <typename Type, size_t nDim>
void Basis<Type, nDim>::apply(const Transform<Type, nDim> &transform)
{
    this->_center.apply(transform);

    for (size_t i = 0; nDim > i; i++)
        this->_axis[i].apply(transform);
}

template <typename Type, size_t nDim>
void Basis<Type, nDim>::undo(const Transform<Type, nDim> &transform)
{
    this->_center.undo(transform);

    for (size_t i = 0; nDim > i; i++)
        this->_axis[i].undo(transform);
}

template <typename Type, size_t nDim>
template <size_t oDim>
void Basis<Type, nDim>::directSetVector(const Vector<Type, oDim> &vector,
                                        const size_t index)
{
    if (nDim <= index)
        throw CALL_EX(IndexViolationBasisException);

    this->_axis[index] = vector;
}

template <typename Type, size_t nDim>
void Basis<Type, nDim>::_orthogonalize(Vector<Type, nDim>(&arr)[nDim])
{
    Vector<Type, nDim> tmp;

    for (size_t i = 0; nDim > i; i++)
    {
        tmp = arr[i];

        for (size_t j = 0; i > j; j++)
            arr[i] -= (tmp & arr[j]) * arr[j];

        arr[i].normalise();
    }
}

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream &stream, const Basis<Type, nDim> &basis)
{
    stream << "Basis: center - " << basis.getCenter() << std::endl;

    for (size_t i = 0; nDim > i; i++)
        stream << "          [" << i << "] - " << basis.getVector(i) \
               << std::endl;

    return stream;
}

template <typename Type>
void Basis2<Type>::checkLeft(void)
{
    if (!this->isLeft())
        return;

    Vector3<Type> tmp1 (this->getVector(0)),
                  tmp2 (this->getVector(1));

    Vector3<Type> res = tmp1 * tmp2;

    if (Type() > res.z)
        this->directSetVector(-tmp2, 1);
}

template <typename Type>
std::ostream& operator << (std::ostream &stream, const Basis2<Type> &basis)
{
    stream << "Basis: center - " << basis.getCenter() << std::endl;

    for (size_t i = 0; 2 > i; i++)
        stream << "          [" << dim_names[i] << "] - " \
               << basis.getVector(i) << std::endl;

    return stream;
}

template <typename Type>
void Basis3<Type>::checkLeft(void)
{
    if (!this->isLeft())
        return;

    Vector3<Type> tmp1 (this->getVector(0)),
                  tmp2 (this->getVector(1)),
                  tmp3 (this->getVector(2));

    Vector3<Type> res = tmp1 * tmp2;

    if (0 > (res & tmp3))
        this->directSetVector(-tmp3, 2);
}

template <typename Type>
std::ostream& operator << (std::ostream &stream, const Basis3<Type> &basis)
{
    stream << "Basis: center - " << basis.getCenter() << std::endl;

    for (size_t i = 0; 3 > i; i++)
        stream << "          [" << dim_names[i] << "] - " \
               << basis.getVector(i) << std::endl;

    return stream;
}

#endif

