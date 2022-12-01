#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <cmath>
#include <string>
#include <cassert>
#include <float.h>

#include "point.h"

static const std::string dim_names[] = { "x", "y", "z" };

template <typename Type, size_t nDim>
template <size_t oDim>
Point<Type, nDim>::Point(const Point<Type, oDim> &point)
{
    size_t lim = nDim;

    if (oDim < lim)
        lim = oDim;

    for (size_t i = 0; nDim > i; i++)
    {
        if (lim > i)
            this->dims[i] = point[i];
        else
            this->dims[i] = Type();
    }
}

template <typename Type, size_t nDim>
Point<Type, nDim>::Point(const std::initializer_list<Type> &point)
    : Point<Type, nDim>()
{
    assert(nDim >= point.size());

    size_t i = 0;
    for (Type value : point)
        this->dims[i++] = value;
}

template <typename Type, size_t nDim>
template <size_t oDim>
Point<Type, nDim> &Point<Type, nDim>::operator = (const Point<Type, oDim> &point)
{
    size_t lim = nDim;

    if (oDim < lim)
        lim = oDim;

    for (size_t i = 0; nDim > i; i++)
    {
        if (lim > i)
            this->dims[i] = point[i];
        else
            this->dims[i] = Type();
    }

    return *this;
}

template <typename Type, size_t nDim>
Type &Point<Type, nDim>::operator [] (const size_t i)
{
    size_t j = i % nDim;

    return this->dims[j];
}

template <typename Type, size_t nDim>
const Type &Point<Type, nDim>::operator [] (const size_t i) const
{
    size_t j = i % nDim;

    return this->dims[j];
}

template <typename Type, size_t nDim>
Point<Type, nDim>::operator bool(void) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON < fabs((double)this->dims[i]))
            return false;

    return true;
}

template <typename Type, size_t nDim>
bool Point<Type, nDim>::operator == (const Point<Type, nDim> &point) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON < fabs((double)(this->dims[i] - point.dims[i])))
            return false;

    return true;
}

template <typename Type, size_t nDim>
bool Point<Type, nDim>::operator != (const Point<Type, nDim> &point) const
{
    for (size_t i = 0; nDim > i; i++)
        if (FLT_EPSILON > fabs((double)(this->dims[i] - point.dims[i])))
            return false;

    return true;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Point<Type, nDim>::operator + (const Point<Type, nDim> &point) const
{
    Point<Type, nDim> out (*this);

    return out += point;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Point<Type, nDim>::operator - (const Point<Type, nDim> &point) const
{
    Point<Type, nDim> out (*this);

    return out -= point;
}

template <typename Type, size_t nDim>
template <typename Other>
Point<Type, nDim> Point<Type, nDim>::operator * (const Other &value) const
{
    Point<Type, nDim> out (*this);

    return out *= value;
}

template <typename Type, size_t nDim>
template <typename Other>
Point<Type, nDim> Point<Type, nDim>::operator / (const Other &value) const
{
    Point<Type, nDim> out (*this);

    return out /= value;
}

template <typename Type, size_t nDim>
Point<Type, nDim> &Point<Type, nDim>::operator += (const Point<Type, nDim> &point)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] += point.dims[i];

    return *this;
}

template <typename Type, size_t nDim>
Point<Type, nDim> &Point<Type, nDim>::operator -= (const Point<Type, nDim> &point)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] -= point.dims[i];

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Point<Type, nDim> &Point<Type, nDim>::operator *= (const Other &value)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] *= value;

    return *this;
}

template <typename Type, size_t nDim>
template <typename Other>
Point<Type, nDim> &Point<Type, nDim>::operator /= (const Other &value)
{
    for (size_t i = 0; nDim > i; i++)
        this->dims[i] /= value;

    return *this;
}

template <typename Type, size_t nDim>
void Point<Type, nDim>::apply(const Transform<Type, nDim> &transform)
{
    Matrix<Type> point (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        point[0][i] = (*this)[i];

    point[0][nDim] = Type(1);
    point *= transform.getMatrix();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = point[0][i] / point[0][nDim];
}

template <typename Type, size_t nDim>
void Point<Type, nDim>::undo(const Transform<Type, nDim> &transform)
{
    Matrix<Type> point (1, nDim + 1);

    for (size_t i = 0; nDim > i; i++)
        point[0][i] = (*this)[i];

    point[0][nDim] = Type(1);
    point *= transform.getInverse();

    for (size_t i = 0; nDim > i; i++)
        (*this)[i] = point[0][i] / point[0][nDim];
}

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Point<Type, nDim> &point)
{
    stream << "[";

    for (size_t i = 0; nDim - 1 > i; i++)
        stream << point[i] << ", ";

    stream << point[nDim - 1] << "]";

    return stream;
}

template <typename Type, size_t nDim>
Type distance(const Point<Type, nDim> &point1,
              const Point<Type, nDim> &point2)
{
    return sqrt(distanceSqr(point1, point2));
}

template <typename Type, size_t nDim>
Type distanceSqr(const Point<Type, nDim> &point1,
                 const Point<Type, nDim> &point2)
{
    Type res = 0;
    Type diff = 0;

    for (size_t i = 0; nDim > i; i++)
    {
        diff = point2[i] - point1[i];
        res += diff * diff;
    }

    return res;
}

template <typename Type>
void Point2<Type>::initProperties(void)
{
    this->x.init(this, &Point2<Type>::setX, &Point2<Type>::getX);
    this->y.init(this, &Point2<Type>::setY, &Point2<Type>::getY);
}

template <typename Type>
template <size_t oDim>
Point2<Type>::Point2(const Point<Type, oDim> &point) : Point<Type, 2>(point)
{
    this->initProperties();
}

template <typename Type>
template <size_t oDim>
Point2<Type> &Point2<Type>::operator = (const Point<Type, oDim> &point)
{
    static_cast<Point<Type, 2> &>(*this) = point;

    return *this;
}

template <typename Type>
Point2<Type> &Point2<Type>::operator = (const Point2<Type> &point)
{
    this->x = point.x;
    this->y = point.y;

    return *this;
}

template <typename Type>
Point2<Type> &Point2<Type>::operator = (const Point3<Type> &point)
{
    this->x = point.x;
    this->y = point.y;

    return *this;
}

template <typename Type>
Point2<Type> Point2<Type>::operator + (const Point2<Type> &point) const
{
    return Point2<Type> (*static_cast<const Point<Type, 2> *>(this) + point);
}

template <typename Type>
Point2<Type> Point2<Type>::operator - (const Point2<Type> &point) const
{
    return Point2<Type> (*static_cast<const Point<Type, 2> *>(this) - point);
}

template <typename Type>
template <typename Other>
Point2<Type> Point2<Type>::operator * (const Other &value) const
{
    return Point2<Type> (*static_cast<const Point<Type, 2> *>(this) * value);
}

template <typename Type>
template <typename Other>
Point2<Type> Point2<Type>::operator / (const Other &value) const
{
    return Point2<Type> (*static_cast<const Point<Type, 2> *>(this) / value);
}

template <typename Type>
Point2<Type> &Point2<Type>::operator += (const Point2<Type> &point)
{
    Point<Type, 2> &tmp = *static_cast<Point<Type, 2> *>(this);
    tmp += point;

    return *this;
}

template <typename Type>
Point2<Type> &Point2<Type>::operator -= (const Point2<Type> &point)
{
    Point<Type, 2> &tmp = *static_cast<Point<Type, 2> *>(this);
    tmp -= point;

    return *this;
}

template <typename Type>
template <typename Other>
Point2<Type> &Point2<Type>::operator *= (const Other &value)
{
    Point<Type, 2> &tmp = *static_cast<Point<Type, 2> *>(this);
    tmp *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Point2<Type> &Point2<Type>::operator /= (const Other &value)
{
    Point<Type, 2> &tmp = *static_cast<Point<Type, 2> *>(this);
    tmp /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Point2<Type> &point)
{
    stream << "{" << dim_names[0] << ": " << point.x << ", " 
           << dim_names[1] << ": " << point.y << "}";

    return stream;
}

template <typename Type>
void Point3<Type>::initProperties(void)
{
    this->x.init(this, &Point3<Type>::setX, &Point3<Type>::getX);
    this->y.init(this, &Point3<Type>::setY, &Point3<Type>::getY);
    this->z.init(this, &Point3<Type>::setZ, &Point3<Type>::getZ);
}

template <typename Type>
template <size_t oDim>
Point3<Type>::Point3(const Point<Type, oDim> &point) : Point<Type, 3>(point)
{
    this->initProperties();
}

template <typename Type>
template <size_t oDim>
Point3<Type> &Point3<Type>::operator = (const Point<Type, oDim> &point)
{
    static_cast<Point<double, 3> &>(*this) = point;

    return *this;
}

template <typename Type>
Point3<Type> &Point3<Type>::operator = (const Point2<Type> &point)
{
    this->x = point.x;
    this->y = point.y;

    return *this;
}

template <typename Type>
Point3<Type> &Point3<Type>::operator = (const Point3<Type> &point)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;

    return *this;
}

template <typename Type>
Point3<Type> Point3<Type>::operator + (const Point3<Type> &point) const
{
    return Point3<Type> (*static_cast<const Point<Type, 3> *>(this) + point);
}

template <typename Type>
Point3<Type> Point3<Type>::operator - (const Point3<Type> &point) const
{
    return Point3<Type> (*static_cast<const Point<Type, 3> *>(this) - point);
}

template <typename Type>
template <typename Other>
Point3<Type> Point3<Type>::operator * (const Other &value) const
{
    return Point3<Type> (*static_cast<const Point<Type, 3> *>(this) * value);
}

template <typename Type>
template <typename Other>
Point3<Type> Point3<Type>::operator / (const Other &value) const
{
    return Point3<Type> (*static_cast<const Point<Type, 3> *>(this) / value);
}

template <typename Type>
Point3<Type> &Point3<Type>::operator += (const Point3<Type> &point)
{
    Point<Type, 3> &tmp = *static_cast<Point<Type, 3> *>(this);
    tmp += point;

    return *this;
}

template <typename Type>
Point3<Type> &Point3<Type>::operator -= (const Point3<Type> &point)
{
    Point<Type, 3> &tmp = *static_cast<Point<Type, 3> *>(this);
    tmp -= point;

    return *this;
}

template <typename Type>
template <typename Other>
Point3<Type> &Point3<Type>::operator *= (const Other &value)
{
    Point<Type, 3> &tmp = *static_cast<Point<Type, 3> *>(this);
    tmp *= value;

    return *this;
}

template <typename Type>
template <typename Other>
Point3<Type> &Point3<Type>::operator /= (const Other &value)
{
    Point<Type, 3> &tmp = *static_cast<Point<Type, 3> *>(this);
    tmp /= value;

    return *this;
}

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Point3<Type> &point)
{
    stream << "{" << dim_names[0] << ": " << point.x << ", " 
           << dim_names[1] << ": " << point.y << ", "
           << dim_names[2] << ": " << point.z << "}";

    return stream;
}

template <typename PointType>
PointType interpolate(const PointType &point1, const PointType &point2,
                      const double t)
{
    double new_t = t;

    if (1 < new_t)
        new_t = 1;
    else if (0 > new_t)
        new_t = 0;

    return point1 * (1 - new_t) + point2 * new_t;
}


#endif

