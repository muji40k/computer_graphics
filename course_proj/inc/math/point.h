#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <cstddef>
#include <initializer_list>

#include "property.h"

#include "transform.h"

template <typename Type, size_t nDim = 3>
class Point : public Transformable<Type, nDim>
{
    private:
        Type dims[nDim] = {0};

    public:
        Point(void) = default;
        template <size_t oDim = nDim>
        Point(const Point<Type, oDim> &point);
        explicit Point(const std::initializer_list<Type> &point);

        template <size_t oDim = nDim>
        Point<Type, nDim> &operator = (const Point<Type, oDim> &point);

        size_t size(void) const { return nDim; };

        Type &operator [] (const size_t i);
        const Type &operator [] (const size_t i) const;

        operator bool(void) const;
        bool operator == (const Point<Type, nDim> &point) const;
        bool operator != (const Point<Type, nDim> &point) const;

        Point<Type, nDim> operator + (const Point<Type, nDim> &point) const;
        Point<Type, nDim> operator - (const Point<Type, nDim> &point) const;
        template <typename Other>
        Point<Type, nDim> operator * (const Other &value) const;
        template <typename Other>
        Point<Type, nDim> operator / (const Other &value) const;

        Point<Type, nDim> &operator += (const Point<Type, nDim> &point);
        Point<Type, nDim> &operator -= (const Point<Type, nDim> &point);
        template <typename Other>
        Point<Type, nDim> &operator *= (const Other &value);
        template <typename Other>
        Point<Type, nDim> &operator /= (const Other &value);

        virtual void apply(const Transform<Type, nDim> &transform) override;
        virtual void undo(const Transform<Type, nDim> &transform) override;
};

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Point<Type, nDim> &point);

template <typename Type, size_t nDim>
Type distance(const Point<Type, nDim> &point1,
              const Point<Type, nDim> &point2);

template <typename Type, size_t nDim>
Type distanceSqr(const Point<Type, nDim> &point1,
                 const Point<Type, nDim> &point2);

template <typename Type>
class Point3;

template <typename Type>
class Point2 : public Point<Type, 2>
{
    private:
        void initProperties(void);

    public:
        Point2(void) : Point<Type, 2>() { this->initProperties(); };
        Point2(const Type &x, const Type &y) : Point<Type, 2>({x, y}) { this->initProperties(); };
        explicit Point2(const std::initializer_list<Type> &list) : Point<Type, 2>(list) { this->initProperties(); };

        template <size_t oDim = 2>
        explicit Point2(const Point<Type, oDim> &point);
        Point2(const Point2<Type> &point) : Point<Type, 2>(point) { this->initProperties(); };
        explicit Point2(const Point3<Type> &point) : Point<Type, 2>(point) { this->initProperties(); };

        template <size_t oDim = 2>
        Point2<Type> &operator = (const Point<Type, oDim> &point);
        Point2<Type> &operator = (const Point2<Type> &point);
        Point2<Type> &operator = (const Point3<Type> &point);

        Property<Point2, Type> x;
        Property<Point2, Type> y;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };

        Point2<Type> operator + (const Point2<Type> &point) const;
        Point2<Type> operator - (const Point2<Type> &point) const;
        template <typename Other>
        Point2<Type> operator * (const Other &value) const;
        template <typename Other>
        Point2<Type> operator / (const Other &value) const;

        Point2<Type> &operator += (const Point2<Type> &point);
        Point2<Type> &operator -= (const Point2<Type> &point);
        template <typename Other>
        Point2<Type> &operator *= (const Other &value);
        template <typename Other>
        Point2<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Point2<Type> &point);

template <typename Type>
class Point3 : public Point<Type, 3>
{
    private:
        void initProperties(void);

    public:
        Point3(void) : Point<Type, 3>() { this->initProperties(); };
        Point3(const Type &x, const Type &y, const Type &z) : Point<Type, 3>({x, y, z}) { this->initProperties(); };
        explicit Point3(const std::initializer_list<Type> &list) : Point<Type, 3>(list) { this->initProperties(); };

        template <size_t oDim = 3>
        explicit Point3(const Point<Type, oDim> &point);
        explicit Point3(const Point2<Type> &point) : Point<Type, 3>(point) { this->initProperties(); };
        Point3(const Point3<Type> &point) : Point<Type, 3>(point) { this->initProperties(); };

        template <size_t oDim = 3>
        Point3<Type> &operator = (const Point<Type, oDim> &point);
        Point3<Type> &operator = (const Point2<Type> &point);
        Point3<Type> &operator = (const Point3<Type> &point);

        Property<Point3, Type> x;
        Property<Point3, Type> y;
        Property<Point3, Type> z;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        void setZ(const Type &value) { (*this)[2] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };
        const Type &getZ(void) const { return (*this)[2]; };

        Point3<Type> operator + (const Point3<Type> &point) const;
        Point3<Type> operator - (const Point3<Type> &point) const;
        template <typename Other>
        Point3<Type> operator * (const Other &value) const;
        template <typename Other>
        Point3<Type> operator / (const Other &value) const;

        Point3<Type> &operator += (const Point3<Type> &point);
        Point3<Type> &operator -= (const Point3<Type> &point);
        template <typename Other>
        Point3<Type> &operator *= (const Other &value);
        template <typename Other>
        Point3<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Point3<Type> &point);

template <typename PointType>
PointType interpolate(const PointType &point1, const PointType &point2,
                      const double t);


#include "point.hpp"

#endif

