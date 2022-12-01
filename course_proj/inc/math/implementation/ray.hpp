#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "ray.h"

template <typename Type, size_t nDim>
Ray<Type, nDim>::Ray(const Point<Type, nDim> &origin,
                     const Vector<Type, nDim> &vector)
    : origin(origin), direction(vector) {}

template <typename Type, size_t nDim>
Ray<Type, nDim>::Ray(const Point<Type, nDim> &start, const Point<Type, nDim> &end)
    : origin(start), direction(end - start) {}

template <typename Type, size_t nDim>
template <size_t oDim>
Ray<Type, nDim> &Ray<Type, nDim>::operator = (const Ray<Type, oDim> &ray)
{
    this->origin = ray.origin;
    this->direction = ray.direction;

    return *this;
}

template <typename Type, size_t nDim>
Ray<Type, nDim>::operator bool(void) const
{
    return this->origin && this->direction;
}

template <typename Type, size_t nDim>
bool Ray<Type, nDim>::operator == (const Ray<Type, nDim> &ray) const
{
    return this->origin == ray.origin && this->direction == ray.direction;
}

template <typename Type, size_t nDim>
bool Ray<Type, nDim>::operator != (const Ray<Type, nDim> &ray) const
{
    return !(*this == ray);
}

template <typename Type, size_t nDim>
const Point<Type, nDim>  Ray<Type, nDim>::getOrigin(void) const
{
    return this->origin;
}

template <typename Type, size_t nDim>
const Vector<Type, nDim> Ray<Type, nDim>::getDirection(void) const
{
    return this->direction;
}

template <typename Type, size_t nDim>
void Ray<Type, nDim>::setOrigin(const Point<Type, nDim> &point)
{
    this->origin = point;
}

template <typename Type, size_t nDim>
void Ray<Type, nDim>::setDirection(const Vector<Type, nDim> &vector)
{
    this->direction = vector;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Ray<Type, nDim>::trace(double t) const
{
    return this->origin + this->direction * t;
}

template <typename Type, size_t nDim>
Point<Type, nDim> Ray<Type, nDim>::operator () (double t) const
{
    return this->trace(t);
}

template <typename Type, size_t nDim>
void Ray<Type, nDim>::apply(const Transform<Type, nDim> &transform)
{
    this->origin.apply(transform);
    this->direction.apply(transform);
}

template <typename Type, size_t nDim>
void Ray<Type, nDim>::undo(const Transform<Type, nDim> &transform)
{
    this->origin.undo(transform);
    this->direction.undo(transform);
}

#endif

