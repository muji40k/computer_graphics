#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <cmath>
#include <string>
#include <cassert>
#include <float.h>

#include "vector.h"

template <typename Type, size_t nDim>
template <size_t oDim>
Vector<Type, nDim>::Vector(const Vector<Type, oDim> &vector)
{
    size_t lim = nDim;

    if (oDim < lim)
        lim = oDim;

    for (size_t i = 0; nDim > i; i++)
    {
        if (lim > i)
            this->dims[i] = vector[i];
        else
            this->dims[i] = Type();
    }
}

template <typename Type, size_t nDim>
Vector<Type, nDim>::Vector(const std::initializer_list<Type> &vector)
    : Vector<Type, nDim>()
{
    assert(nDim >= vector.size());

    size_t i = 0;
    for (Type value : vector)
        this->dims[i++] = value;
}

template <typename Type, size_t nDim>
Vector<Type, nDim>::Vector(const Point<Type, nDim> &start,
                           const Point<Type, nDim> &end)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] = end[i] - start[i];
}

template <typename Type, size_t nDim>
template <size_t oDim>
Vector<Type, nDim> &Vector<Type, nDim>::operator = (const Vector<Type, oDim> &vector)
{
    size_t lim = nDim;

    if (oDim < lim)
        lim = oDim;

    for (size_t i = 0; nDim > i; i++)
    {
        if (lim > i)
            this->dims[i] = vector[i];
        else
            this->dims[i] = Type();
    }

    return *this;
}

template <typename Type, size_t nDim>
Type Vector<Type, nDim>::length(void) const
{
    return std::sqrt(this->lengthSqr());
}

template <typename Type, size_t nDim>
Type Vector<Type, nDim>::lengthSqr(void) const
{
    Type len = 0;

    for (size_t i = 0; nDim > i; i++)
        len += this->dims[i] * this->dims[i];

    return len;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> &Vector<Type, nDim>::normalise(void)
{
    Type len = this->length();

    for (size_t i = 0; nDim > i; i++)
        this->dims[i] /= len;

    return *this;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> Vector<Type, nDim>::normalised(void) const
{
    Vector<Type, nDim> out (*this);

    return out.normalise();
}

template <typename Type, size_t nDim>
Type &Vector<Type, nDim>::operator [] (const size_t i)
{
    size_t j = i % nDim;

    return this->dims[j];
}

template <typename Type, size_t nDim>
const Type &Vector<Type, nDim>::operator [] (const size_t i) const
{
    size_t j = i % nDim;

    return this->dims[j];
}

template <typename Type, size_t nDim>
Vector<Type, nDim>::operator bool(void) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON < fabs((double)this->dims[i]))
            return true;

    return false;
}

template <typename Type, size_t nDim>
bool Vector<Type, nDim>::operator == (const Vector<Type, nDim> &vector) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON < fabs((double)(this->dims[i] - vector.dims[i])))
            return false;

    return true;
}

template <typename Type, size_t nDim>
bool Vector<Type, nDim>::operator != (const Vector<Type, nDim> &vector) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON > fabs((double)(this->dims[i] - vector.dims[i])))
            return false;

    return true;
}

template <typename Type, size_t nDim>
Type Vector<Type, nDim>::operator & (const Vector<Type, nDim> &vector) const
{
    Type value = 0;

    for (size_t i = 0; nDim > i; i++)
        value += this->dims[i] * vector.dims[i];

    return value;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Vector<Type, nDim>::operator + (const Point<Type, nDim> &point) const
{
    Point<Type, nDim> out (point);

    for (size_t i = 0; nDim > i; i++)
        out[i] += this->dims[i];

    return out;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> Vector<Type, nDim>::operator + (const Vector<Type, nDim> &vector) const
{
    Vector<Type, nDim> out (*this);

    return out += vector;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> Vector<Type, nDim>::operator - (const Vector<Type, nDim> &vector) const
{
    Vector<Type, nDim> out (*this);

    return out -= vector;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> Vector<Type, nDim>::operator - (void) const
{
    Vector<Type, nDim> out (*this);

    return out *= -1;
}

template <typename Type, size_t nDim>
template <typename Other>
Vector<Type, nDim> Vector<Type, nDim>::operator * (const Other &value) const
{
    Vector<Type, nDim> out (*this);

    return out *= value;
}

template <typename Type, size_t nDim>
template <typename Other>
Vector<Type, nDim> Vector<Type, nDim>::operator / (const Other &value) const
{
    Vector<Type, nDim> out (*this);

    return out /= value;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> &Vector<Type, nDim>::operator += (const Vector<Type, nDim> &vector)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] += vector.dims[i];

    return *this;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> &Vector<Type, nDim>::operator -= (const Vector<Type, nDim> &vector)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] -= vector.dims[i];

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Vector<Type, nDim> &Vector<Type, nDim>::operator *= (const Other &value)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] *= value;

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Vector<Type, nDim> &Vector<Type, nDim>::operator /= (const Other &value)
{
    if (FLT_EPSILON > fabs(double(value)))
        throw CALL_EX(DivisionByZeroVectorException);

    for (size_t i = 0; nDim > i; i++)
        this->dims[i] /= value;

    return *this;
}

template <typename Type, size_t nDim>
void Vector<Type, nDim>::apply(const Transform<Type, nDim> &transform)
{
    Matrix<Type> vector (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        vector[0][i] = (*this)[i];

    vector[0][nDim] = Type();
    vector *= transform.getMatrix();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = vector[0][i];
}

template <typename Type, size_t nDim>
void Vector<Type, nDim>::undo(const Transform<Type, nDim> &transform)
{
    Matrix<Type> vector (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        vector[0][i] = (*this)[i];

    vector[0][nDim] = Type();
    vector *= transform.getInverse();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = vector[0][i];
}

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Vector<Type, nDim> &vector)
{
    stream << "[";

    for (size_t i = 0; nDim - 1 > i; i++)
        stream << vector[i] << ", ";

    stream << vector[nDim - 1] << "]";

    return stream;
}

template <typename Type, size_t nDim>
Vector<Type, nDim> operator < (const Point<Type, nDim> &end,
                               const Point<Type, nDim> &start)
{
    return Vector<Type, nDim>(start, end);
}

template <typename Type, size_t nDim>
Vector<Type, nDim> operator > (const Point<Type, nDim> &start,
                               const Point<Type, nDim> &end)
{
    return Vector<Type, nDim>(start, end);
}

template <typename Type>
void Vector2<Type>::initProperties(void)
{
    this->x.init(this, &Vector2<Type>::setX, &Vector2<Type>::getX);
    this->y.init(this, &Vector2<Type>::setY, &Vector2<Type>::getY);
}

template <typename Type>
template <size_t oDim>
Vector2<Type>::Vector2(const Vector<Type, oDim> &vector) : Vector<Type, 2>(vector)
{
    this->initProperties();
}

template <typename Type>
template <size_t oDim>
Vector2<Type> &Vector2<Type>::operator = (const Vector<Type, oDim> &vector)
{
    static_cast<Vector<Type, 2> &>(*this) = vector;

    return *this;
}

template <typename Type>
Vector2<Type> &Vector2<Type>::operator = (const Vector2<Type> &vector)
{
    this->x = vector.x;
    this->y = vector.y;

    return *this;
}

template <typename Type>
Vector2<Type> &Vector2<Type>::operator = (const Vector3<Type> &vector)
{
    this->x = vector.x;
    this->y = vector.y;

    return *this;
}

template <typename Type>
Vector2<Type> &Vector2<Type>::normalise(void)
{
    this->Vector<Type, 2>::normalise();

    return *this;
}

template <typename Type>
Vector2<Type> Vector2<Type>::normalised(void) const
{
    Vector2<Type> out (*this);

    return out.normalise();
}

template <typename Type>
Point2<Type> Vector2<Type>::operator + (const Point2<Type> &point) const
{
    return Point2<Type> (*static_cast<const Vector<Type, 2> *>(this) +
                         static_cast<const Point<Type, 2> &>(point));
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator + (const Vector2<Type> &vector) const
{
    return Vector2<Type> (*static_cast<const Vector<Type, 2> *>(this) + vector);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator - (const Vector2<Type> &vector) const
{
    return Vector2<Type> (*static_cast<const Vector<Type, 2> *>(this) - vector);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator - (void) const
{
    return Vector2<Type> (-*static_cast<const Vector<Type, 2> *>(this));
}

template <typename Type>
template <typename Other>
Vector2<Type> Vector2<Type>::operator * (const Other &value) const
{
    return Vector2<Type> (*static_cast<const Vector<Type, 2> *>(this) * value);
}

template <typename Type>
template <typename Other>
Vector2<Type> Vector2<Type>::operator / (const Other &value) const
{
    return Vector2<Type> (*static_cast<const Vector<Type, 2> *>(this) / value);
}

template <typename Type>
Vector2<Type> &Vector2<Type>::operator += (const Vector2<Type> &vector)
{
    Vector<Type, 2> &tmp = *static_cast<Vector<Type, 2> *>(this);
    tmp += vector;

    return *this;
}

template <typename Type>
Vector2<Type> &Vector2<Type>::operator -= (const Vector2<Type> &vector)
{
    Vector<Type, 2> &tmp = *static_cast<Vector<Type, 2> *>(this);
    tmp -= vector;

    return *this;
}

template <typename Type>
template <typename Other>
Vector2<Type> &Vector2<Type>::operator *= (const Other &value)
{
    Vector<Type, 2> &tmp = *static_cast<Vector<Type, 2> *>(this);
    tmp *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Vector2<Type> &Vector2<Type>::operator /= (const Other &value)
{
    Vector<Type, 2> &tmp = *static_cast<Vector<Type, 2> *>(this);
    tmp /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Vector2<Type> &vector)
{
    stream << "{" << dim_names[0] << ": " << vector.x << ", " 
           << dim_names[1] << ": " << vector.y << "}";

    return stream;
}

template <typename Type>
Vector2<Type> operator < (const Point2<Type> &end, const Point2<Type> &start)
{
    return Vector2<Type>(start, end);
}

template <typename Type>
Vector2<Type> operator > (const Point2<Type> &start, const Point2<Type> &end)
{
    return Vector2<Type>(start, end);
}

template <typename Type>
void Vector3<Type>::initProperties(void)
{
    this->x.init(this, &Vector3<Type>::setX, &Vector3<Type>::getX);
    this->y.init(this, &Vector3<Type>::setY, &Vector3<Type>::getY);
    this->z.init(this, &Vector3<Type>::setZ, &Vector3<Type>::getZ);
}

template <typename Type>
template <size_t oDim>
Vector3<Type>::Vector3(const Vector<Type, oDim> &vector) : Vector<Type, 3>(vector)
{
    this->initProperties();
}

template <typename Type>
template <size_t oDim>
Vector3<Type> &Vector3<Type>::operator = (const Vector<Type, oDim> &vector)
{
    static_cast<Vector<double, 3> &>(*this) = vector;

    return *this;
}

template <typename Type>
Vector3<Type> &Vector3<Type>::operator = (const Vector2<Type> &vector)
{
    this->x = vector.x;
    this->y = vector.y;

    return *this;
}

template <typename Type>
Vector3<Type> &Vector3<Type>::operator = (const Vector3<Type> &vector)
{
    this->x = vector.x;
    this->y = vector.y;
    this->z = vector.z;

    return *this;
}


template <typename Type>
Vector3<Type> &Vector3<Type>::normalise(void)
{
    this->Vector<Type, 3>::normalise();

    return *this;
}

template <typename Type>
Vector3<Type> Vector3<Type>::normalised(void) const
{
    Vector3<Type> out (*this);

    return out.normalise();
}

template <typename Type>
Point3<Type> Vector3<Type>::operator + (const Point3<Type> &point) const
{
    return Point3<Type> (*static_cast<const Vector<Type, 3> *>(this) +
                         static_cast<const Point<Type, 3> &>(point));
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator + (const Vector3<Type> &vector) const
{
    return Vector3<Type> (*static_cast<const Vector<Type, 3> *>(this) + vector);
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator - (const Vector3<Type> &vector) const
{
    return Vector3<Type> (*static_cast<const Vector<Type, 3> *>(this) - vector);
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator - (void) const
{
    return Vector3<Type> (-*static_cast<const Vector<Type, 3> *>(this));
}

template <typename Type>
Vector3<Type> Vector3<Type>::operator * (const Vector3<Type> &vector) const
{
    Vector3<Type> out (*this);

    return out *= vector;
}

template <typename Type>
template <typename Other>
Vector3<Type> Vector3<Type>::operator * (const Other &value) const
{
    return Vector3<Type> (*static_cast<const Vector<Type, 3> *>(this) * value);
}

template <typename Type>
template <typename Other>
Vector3<Type> Vector3<Type>::operator / (const Other &value) const
{
    return Vector3<Type> (*static_cast<const Vector<Type, 3> *>(this) / value);
}

template <typename Type>
Vector3<Type> &Vector3<Type>::operator += (const Vector3<Type> &vector)
{
    Vector<Type, 3> &tmp = *static_cast<Vector<Type, 3> *>(this);
    tmp += vector;

    return *this;
}

template <typename Type>
Vector3<Type> &Vector3<Type>::operator -= (const Vector3<Type> &vector)
{
    Vector<Type, 3> &tmp = *static_cast<Vector<Type, 3> *>(this);
    tmp -= vector;

    return *this;
}

template <typename Type>
Vector3<Type> &Vector3<Type>::operator *= (const Vector3<Type> &vector)
{
    double x = this->x, y = this->y, z = this->z;

    this->x = y * vector.z - z * vector.y;
    this->y = - (x * vector.z - z * vector.x);
    this->z = x * vector.y - y * vector.x;

    return *this;
}

template <typename Type>
template <typename Other>
Vector3<Type> &Vector3<Type>::operator *= (const Other &value)
{
    Vector<Type, 3> &tmp = *static_cast<Vector<Type, 3> *>(this);
    tmp *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Vector3<Type> &Vector3<Type>::operator /= (const Other &value)
{
    Vector<Type, 3> &tmp = *static_cast<Vector<Type, 3> *>(this);
    tmp /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Vector3<Type> &vector)
{
    stream << "{" << dim_names[0] << ": " << vector.x << ", " 
           << dim_names[1] << ": " << vector.y << ", "
           << dim_names[2] << ": " << vector.z << "}";

    return stream;
}

template <typename Type>
Vector3<Type> operator < (const Point3<Type> &end, const Point3<Type> &start)
{
    return Vector3<Type>(start, end);
}

template <typename Type>
Vector3<Type> operator > (const Point3<Type> &start, const Point3<Type> &end)
{
    return Vector3<Type>(start, end);
}

#endif

