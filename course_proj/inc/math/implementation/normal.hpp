#ifndef _NORMAL_HPP_
#define _NORMAL_HPP_

#include "normal.h"

template <typename Type, size_t nDim>
template <size_t oDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator = (const Vector<Type, oDim> &vector)
{
    static_cast<Vector<Type, nDim> &>(*this) = vector;

    return *this;
}

template <typename Type, size_t nDim>
template <size_t oDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator = (const Normal<Type, oDim> &normal)
{
    static_cast<Vector<Type, nDim> &>(*this) = normal;

    return *this;
}

template <typename Type, size_t nDim>
Normal<Type, nDim> &Normal<Type, nDim>::normalise(void)
{
    this->Vector<Type, nDim>::normalise();

    return *this;
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::normalised(void) const
{
    Normal<Type, nDim> out (*this);

    return out.normalise();
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::operator + (const Vector<Type, nDim> &vector) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) + vector);
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::operator - (const Vector<Type, nDim> &vector) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) - vector);
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::operator + (const Normal<Type, nDim> &normal) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) + static_cast<const Vector<Type, nDim> &>(normal));
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::operator - (const Normal<Type, nDim> &normal) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) - static_cast<const Vector<Type, nDim> &>(normal));
}

template <typename Type, size_t nDim>
Normal<Type, nDim> Normal<Type, nDim>::operator - (void) const
{
    return Normal<Type, nDim>(-static_cast<const Vector<Type, nDim> &>(*this));
}

template <typename Type, size_t nDim>
template <typename Other>
Normal<Type, nDim> Normal<Type, nDim>::operator * (const Other &value) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) * value);
}

template <typename Type, size_t nDim>
template <typename Other>
Normal<Type, nDim> Normal<Type, nDim>::operator / (const Other &value) const
{
    return Normal<Type, nDim>(static_cast<const Vector<Type, nDim> &>(*this) / value);
}

template <typename Type, size_t nDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator += (const Vector<Type, nDim> &vector)
{
    static_cast<Vector<Type, nDim> &>(*this) += vector;

    return *this;
}

template <typename Type, size_t nDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator -= (const Vector<Type, nDim> &vector)
{
    static_cast<Vector<Type, nDim> &>(*this) -= vector;

    return *this;
}

template <typename Type, size_t nDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator += (const Normal<Type, nDim> &normal)
{
    static_cast<Vector<Type, nDim> &>(*this) += static_cast<const Vector<Type, nDim> &>(normal);

    return *this;
}

template <typename Type, size_t nDim>
Normal<Type, nDim> &Normal<Type, nDim>::operator -= (const Normal<Type, nDim> &normal)
{
    static_cast<Vector<Type, nDim> &>(*this) -= static_cast<const Vector<Type, nDim> &>(normal);

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Normal<Type, nDim> &Normal<Type, nDim>::operator *= (const Other &value)
{
    static_cast<Vector<Type, nDim> &>(*this) *= value;

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Normal<Type, nDim> &Normal<Type, nDim>::operator /= (const Other &value)
{
    static_cast<Vector<Type, nDim> &>(*this) /= value;

    return *this;
}

template <typename Type, size_t nDim>
void Normal<Type, nDim>::apply(const Transform<Type, nDim> &transform)
{
    Matrix<Type> normal (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        normal[0][i] = (*this)[i];

    normal[0][nDim] = Type();
    normal *= transform.getInverse().getTransposed();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = normal[0][i];
}

template <typename Type, size_t nDim>
void Normal<Type, nDim>::undo(const Transform<Type, nDim> &transform)
{
    Matrix<Type> normal (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        normal[0][i] = (*this)[i];

    normal[0][nDim] = Type();
    normal *= transform.getMatrix().getTransposed();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = normal[0][i];
}

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Normal<Type, nDim> &normal)
{
    return stream << "n" << static_cast<const Vector<Type, nDim> &>(normal);
}

template <typename Type>
void Normal2<Type>::initProperties(void)
{
    this->x.init(this, &Normal2<Type>::setX, &Normal2<Type>::getX);
    this->y.init(this, &Normal2<Type>::setY, &Normal2<Type>::getY);
}

template <typename Type>
template <size_t oDim>
Normal2<Type> &Normal2<Type>::operator = (const Normal<Type, oDim> &normal)
{
    static_cast<Normal<Type, 2> &>(*this) = normal;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator = (const Normal2<Type> &normal)
{
    static_cast<Normal<Type, 2> &>(*this) = normal;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator = (const Normal3<Type> &normal)
{
    static_cast<Normal<Type, 2> &>(*this) = normal;

    return *this;
}

template <typename Type>
template <size_t oDim>
Normal2<Type> &Normal2<Type>::operator = (const Vector<Type, oDim> &vector)
{
    static_cast<Normal<Type, 2> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator = (const Vector2<Type> &vector)
{
    static_cast<Normal<Type, 2> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator = (const Vector3<Type> &vector)
{
    static_cast<Normal<Type, 2> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::normalise(void)
{
    static_cast<Normal<Type, 2> &>(*this).normalise();

    return *this;
}

template <typename Type>
Normal2<Type> Normal2<Type>::normalised(void) const
{
    return Normal2<Type>(static_cast<Normal<Type, 2> &>(*this).normalised());
}

template <typename Type>
Normal2<Type> Normal2<Type>::operator + (const Normal2<Type> &normal) const
{
    return Normal2<Type>(static_cast<const Normal<Type, 2> &>(*this)
                         + static_cast<const Normal<Type, 2> &>(normal));
}

template <typename Type>
Normal2<Type> Normal2<Type>::operator - (const Normal2<Type> &normal) const
{
    return Normal2<Type>(static_cast<const Normal<Type, 2> &>(*this)
                         - static_cast<const Normal<Type, 2> &>(normal));
}

template <typename Type>
Normal2<Type> Normal2<Type>::operator + (const Vector2<Type> &vector) const
{
    return Normal2<Type>(static_cast<const Vector<Type, 2> &>(*this)
                         + vector);
}

template <typename Type>
Normal2<Type> Normal2<Type>::operator - (const Vector2<Type> &vector) const
{
    return Normal2<Type>(static_cast<const Vector<Type, 2> &>(*this)
                         + vector);
}

template <typename Type>
Normal2<Type> Normal2<Type>::operator - (void) const
{
    return Normal2<Type>(-static_cast<const Normal<Type, 2> &>(*this));
}

template <typename Type>
template <typename Other>
Normal2<Type> Normal2<Type>::operator * (const Other &value) const
{
    return Normal2<Type>(static_cast<const Normal<Type, 2> &>(*this) * value);
}

template <typename Type>
template <typename Other>
Normal2<Type> Normal2<Type>::operator / (const Other &value) const
{
    return Normal2<Type>(static_cast<const Normal<Type, 2> &>(*this) / value);
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator += (const Normal2<Type> &normal)
{
    static_cast<Normal<Type, 2> &>(*this) += static_cast<Normal<Type, 2> &>(normal);

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator -= (const Normal2<Type> &normal)
{
    static_cast<Normal<Type, 2> &>(*this) -= static_cast<const Normal<Type, 2> &>(normal);

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator += (const Vector2<Type> &vector)
{
    static_cast<Normal<Type, 2> &>(*this) += vector;

    return *this;
}

template <typename Type>
Normal2<Type> &Normal2<Type>::operator -= (const Vector2<Type> &vector)
{
    static_cast<Normal<Type, 2> &>(*this) -= vector;

    return *this;
}

template <typename Type>
template <typename Other>
Normal2<Type> &Normal2<Type>::operator *= (const Other &value)
{
    static_cast<Normal<Type, 2> &>(*this) *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Normal2<Type> &Normal2<Type>::operator /= (const Other &value)
{
    static_cast<Normal<Type, 2> &>(*this) /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Normal2<Type> &normal)
{
    return stream << "n" << Vector2<Type>(normal);
}

template <typename Type>
void Normal3<Type>::initProperties(void)
{
    this->x.init(this, &Normal3<Type>::setX, &Normal3<Type>::getX);
    this->y.init(this, &Normal3<Type>::setY, &Normal3<Type>::getY);
    this->z.init(this, &Normal3<Type>::setZ, &Normal3<Type>::getZ);
}

template <typename Type>
template <size_t oDim>
Normal3<Type> &Normal3<Type>::operator = (const Normal<Type, oDim> &normal)
{
    static_cast<Normal<Type, 3> &>(*this) = normal;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator = (const Normal2<Type> &normal)
{
    static_cast<Normal<Type, 3> &>(*this) = normal;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator = (const Normal3<Type> &normal)
{
    static_cast<Normal<Type, 3> &>(*this) = normal;

    return *this;
}

template <typename Type>
template <size_t oDim>
Normal3<Type> &Normal3<Type>::operator = (const Vector<Type, oDim> &vector)
{
    static_cast<Normal<Type, 3> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator = (const Vector2<Type> &vector)
{
    static_cast<Normal<Type, 3> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator = (const Vector3<Type> &vector)
{
    static_cast<Normal<Type, 3> &>(*this) = vector;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::normalise(void)
{
    static_cast<Normal<Type, 3> &>(*this).normalise();

    return *this;
}

template <typename Type>
Normal3<Type> Normal3<Type>::normalised(void) const
{
    return Normal3<Type>(static_cast<Normal<Type, 3> &>(*this).normalised());
}

template <typename Type>
Normal3<Type> Normal3<Type>::operator + (const Normal3<Type> &normal) const
{
    return Normal3<Type>(static_cast<const Normal<Type, 3> &>(*this)
                         + static_cast<const Normal<Type, 3> &>(normal));
}

template <typename Type>
Normal3<Type> Normal3<Type>::operator - (const Normal3<Type> &normal) const
{
    return Normal2<Type>(static_cast<const Normal<Type, 3> &>(*this)
                         - static_cast<const Normal<Type, 3> &>(normal));
}

template <typename Type>
Normal3<Type> Normal3<Type>::operator + (const Vector3<Type> &vector) const
{
    return Normal3<Type>(static_cast<const Vector<Type, 3> &>(*this)
                         + vector);
}

template <typename Type>
Normal3<Type> Normal3<Type>::operator - (const Vector3<Type> &vector) const
{
    return Normal3<Type>(static_cast<const Vector<Type, 3> &>(*this)
                         + vector);
}

template <typename Type>
Normal3<Type> Normal3<Type>::operator - (void) const
{
    return Normal3<Type>(-static_cast<const Normal<Type, 3> &>(*this));
}

template <typename Type>
template <typename Other>
Normal3<Type> Normal3<Type>::operator * (const Other &value) const
{
    return Normal3<Type>(static_cast<const Normal<Type, 3> &>(*this) * value);
}

template <typename Type>
template <typename Other>
Normal3<Type> Normal3<Type>::operator / (const Other &value) const
{
    return Normal3<Type>(static_cast<const Normal<Type, 3> &>(*this) / value);
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator += (const Normal3<Type> &normal)
{
    static_cast<Normal<Type, 3> &>(*this) += static_cast<const Normal<Type, 3> &>(normal);

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator -= (const Normal3<Type> &normal)
{
    static_cast<Normal<Type, 3> &>(*this) -= static_cast<const Normal<Type, 3> &>(normal);

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator += (const Vector3<Type> &vector)
{
    static_cast<Normal<Type, 3> &>(*this) += vector;

    return *this;
}

template <typename Type>
Normal3<Type> &Normal3<Type>::operator -= (const Vector3<Type> &vector)
{
    static_cast<Normal<Type, 3> &>(*this) -= vector;

    return *this;
}

template <typename Type>
template <typename Other>
Normal3<Type> &Normal3<Type>::operator *= (const Other &value)
{
    static_cast<Normal<Type, 3> &>(*this) *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Normal3<Type> &Normal3<Type>::operator /= (const Other &value)
{
    static_cast<Normal<Type, 3> &>(*this) /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Normal3<Type> &normal)
{
    return stream << "n" << Vector3<Type>(normal);
}
#endif

