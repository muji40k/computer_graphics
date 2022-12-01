#ifndef _RAY_H_
#define _RAY_H_

#include "transform.h"
#include "point.h"
#include "vector.h"

template <typename Type, size_t nDim = 3>
class Ray : public Transformable<Type, nDim>
{
    private:
        Point<Type, nDim> origin;
        Vector<Type, nDim> direction;

    public:
        Ray(void) = default;
        Ray(const Ray<Type, nDim> &ray) : origin(ray.origin), direction(ray.direction) {};
        Ray(Ray<Type, nDim> &&ray) : origin(ray.origin), direction(ray.direction) {};
        Ray(const Point<Type, nDim> &origin, const Vector<Type, nDim> &vector);
        Ray(const Point<Type, nDim> &start, const Point<Type, nDim> &end);

        template <size_t oDim = nDim>
        Ray<Type, nDim> &operator = (const Ray<Type, oDim> &ray);

        operator bool(void) const;
        bool operator == (const Ray<Type, nDim> &ray) const;
        bool operator != (const Ray<Type, nDim> &ray) const;

        const Point<Type, nDim>  getOrigin(void)    const;
        const Vector<Type, nDim> getDirection(void) const;
        void setOrigin(const Point<Type, nDim> &point);
        void setDirection(const Vector<Type, nDim> &vector);

        Point<Type, nDim> trace(double t) const;
        Point<Type, nDim> operator () (double t) const;

        virtual void apply(const Transform<Type, nDim> &transform) override;
        virtual void undo(const Transform<Type, nDim> &transform) override;
};

template <typename Type>
class Ray3;

template <typename Type>
class Ray2 : public Ray<Type, 2>
{
    public:
        Ray2(void) : Ray<Type, 2>() {};
        Ray2(const Ray2<Type> &ray) : Ray<Type, 2>(ray) {};
        Ray2(Ray2<Type> &&ray) : Ray<Type, 2>(ray) {};
        Ray2(const Point2<Type> &origin, const Vector2<Type> &vector)
            : Ray<Type, 2> (origin, vector) {};
        Ray2(const Point2<Type> &start, const Point2<Type> &end)
            : Ray<Type, 2> (start, end) {};

        template <size_t oDim = 2>
        Ray2<Type> &operator = (const Ray<Type, oDim> &ray)
        { static_cast<Ray<Type, 2> &>(*this) = ray; return *this; }
        Ray2<Type> &operator = (const Ray2<Type> &ray)
        { static_cast<Ray<Type, 2> &>(*this) = ray; return *this; }
        Ray2<Type> &operator = (const Ray3<Type> &ray)
        { static_cast<Ray<Type, 2> &>(*this) = ray; return *this; }

        const Point2<Type>  getOrigin(void) const
        { return Point2<Type>(this->Ray<Type, 2>::getOrigin()); };
        const Vector2<Type> getDirection(void) const
        { return Vector2<Type>(this->Ray<Type, 2>::getDirection()); };

        Point2<Type> trace(double t) const
        { return Point2<Type> (this->Ray<Type, 2>::trace(t)); };
        Point2<Type> operator () (double t) const
        { return Point2<Type> (this->Ray<Type, 2>::trace(t)); };
};

template <typename Type>
class Ray3 : public Ray<Type, 3>
{
    public:
        Ray3(void) : Ray<Type, 3>() {};
        Ray3(const Ray3<Type> &ray) : Ray<Type, 3>(ray) {};
        Ray3(Ray3<Type> &&ray) : Ray<Type, 3>(ray) {};
        Ray3(const Point3<Type> &origin, const Vector3<Type> &vector)
            : Ray<Type, 3> (origin, vector) {};
        Ray3(const Point3<Type> &start, const Point3<Type> &end)
            : Ray<Type, 3> (start, end) {};

        template <size_t oDim = 3>
        Ray3<Type> &operator = (const Ray<Type, oDim> &ray)
        { static_cast<Ray<Type, 3> &>(*this) = ray; return *this; }
        Ray3<Type> &operator = (const Ray2<Type> &ray)
        { static_cast<Ray<Type, 3> &>(*this) = ray; return *this; }
        Ray3<Type> &operator = (const Ray3<Type> &ray)
        { static_cast<Ray<Type, 3> &>(*this) = ray; return *this; }

        const Point3<Type>  getOrigin(void) const
        { return Point3<Type>(this->Ray<Type, 3>::getOrigin()); };
        const Vector3<Type> getDirection(void) const
        { return Vector3<Type>(this->Ray<Type, 3>::getDirection()); };

        Point3<Type> trace(double t) const
        { return Point3<Type> (this->Ray<Type, 3>::trace(t)); };
        Point3<Type> operator () (double t) const
        { return Point3<Type> (this->Ray<Type, 3>::trace(t)); };
};

#include "ray.hpp"

#endif

