#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cstddef>
#include <initializer_list>

#include "property.h"
#include "base_exception.h"

#include "transform.h"
#include "point.h"

template <typename Type, size_t nDim = 3>
class Vector : public Transformable<Type, nDim>
{
    private:
        Type dims[nDim] = {0};

    public:
        Vector(void) = default;
        template <size_t oDim = nDim>
        Vector(const Vector<Type, oDim> &vector);
        explicit Vector(const std::initializer_list<Type> &vector);

        Vector(const Point<Type, nDim> &start, const Point<Type, nDim> &end);

        template <size_t oDim = nDim>
        Vector<Type, nDim> &operator = (const Vector<Type, oDim> &vector);

        size_t size(void) const { return nDim; };

        Type length(void) const;
        Type lengthSqr(void) const;

        Vector<Type, nDim> &normalise(void);
        Vector<Type, nDim> normalised(void) const;

        Type &operator [] (const size_t i);
        const Type &operator [] (const size_t i) const;

        operator bool(void) const;
        bool operator == (const Vector<Type, nDim> &vector) const;
        bool operator != (const Vector<Type, nDim> &vector) const;

        Type operator & (const Vector<Type, nDim> &vector) const;
        Point<Type, nDim> operator + (const Point<Type, nDim> &point) const;

        Vector<Type, nDim> operator + (const Vector<Type, nDim> &vector) const;
        Vector<Type, nDim> operator - (const Vector<Type, nDim> &vector) const;
        Vector<Type, nDim> operator - (void) const;
        template <typename Other>
        Vector<Type, nDim> operator * (const Other &value) const;
        template <typename Other>
        Vector<Type, nDim> operator / (const Other &value) const;

        Vector<Type, nDim> &operator += (const Vector<Type, nDim> &vector);
        Vector<Type, nDim> &operator -= (const Vector<Type, nDim> &vector);
        template <typename Other>
        Vector<Type, nDim> &operator *= (const Other &value);
        template <typename Other>
        Vector<Type, nDim> &operator /= (const Other &value);

        virtual void apply(const Transform<Type, nDim> &transform) override;
        virtual void undo(const Transform<Type, nDim> &transform) override;
};

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Vector<Type, nDim> &vector);

template <typename Type, size_t nDim>
Vector<Type, nDim> operator < (const Point<Type, nDim> &end,
                               const Point<Type, nDim> &start);

template <typename Type, size_t nDim>
Vector<Type, nDim> operator > (const Point<Type, nDim> &start,
                               const Point<Type, nDim> &end);

template <typename Type, size_t nDim, typename Other>
Vector<Type, nDim> operator * (const Other &value, const Vector<Type, nDim> &vector)
{ return vector * value; }

template <typename Type, size_t nDim>
Point<Type, nDim> operator + (const Point<Type, nDim> &point,
                              const Vector<Type, nDim> &vector)
{ return vector + point; }

template <typename Type>
class Vector3;

template <typename Type>
class Vector2 : public Vector<Type, 2>
{
    private:
        void initProperties(void);

    public:
        Vector2(void) : Vector<Type, 2>() { this->initProperties(); };
        Vector2(const Type &x, const Type &y) : Vector<Type, 2>({x, y}) { this->initProperties(); };
        explicit Vector2(const std::initializer_list<Type> &list) : Vector<Type, 2>(list) { this->initProperties(); };

        Vector2(const Point2<Type> &start, const Point2<Type> &end) : Vector<Type, 2>(start, end) { this->initProperties(); };

        template <size_t oDim = 2>
        explicit Vector2(const Vector<Type, oDim> &vector);
        Vector2(const Vector2<Type> &vector) : Vector<Type, 2>(vector) { this->initProperties(); };
        explicit Vector2(const Vector3<Type> &vector) : Vector<Type, 2>(vector) { this->initProperties(); };

        template <size_t oDim = 2>
        Vector2<Type> &operator = (const Vector<Type, oDim> &vector);
        Vector2<Type> &operator = (const Vector2<Type> &vector);
        Vector2<Type> &operator = (const Vector3<Type> &vector);

        Vector2<Type> &normalise(void);
        Vector2<Type> normalised(void) const;

        Property<Vector2, Type> x;
        Property<Vector2, Type> y;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };

        Point2<Type> operator + (const Point2<Type> &point) const;

        Vector2<Type> operator + (const Vector2<Type> &vector) const;
        Vector2<Type> operator - (const Vector2<Type> &vector) const;
        Vector2<Type> operator - (void) const;
        template <typename Other>
        Vector2<Type> operator * (const Other &value) const;
        template <typename Other>
        Vector2<Type> operator / (const Other &value) const;

        Vector2<Type> &operator += (const Vector2<Type> &vector);
        Vector2<Type> &operator -= (const Vector2<Type> &vector);
        template <typename Other>
        Vector2<Type> &operator *= (const Other &value);
        template <typename Other>
        Vector2<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Vector2<Type> &vector);

template <typename Type>
Vector2<Type> operator < (const Point2<Type> &end, const Point2<Type> &start);

template <typename Type>
Vector2<Type> operator > (const Point2<Type> &start, const Point2<Type> &end);

template <typename Type, typename Other>
Vector2<Type> operator * (const Other &value, const Vector2<Type> &vector)
{ return vector * value; }

template <typename Type>
Point2<Type> operator + (const Point2<Type> &point, const Vector2<Type> &vector)
{ return vector + point; }

template <typename Type>
class Vector3 : public Vector<Type, 3>
{
    private:
        void initProperties(void);

    public:
        Vector3(void) : Vector<Type, 3>() { this->initProperties(); };
        Vector3(const Type &x, const Type &y, const Type &z) : Vector<Type, 3>({x, y, z}) { this->initProperties(); };
        explicit Vector3(const std::initializer_list<Type> &list) : Vector<Type, 3>(list) { this->initProperties(); };

        Vector3(const Point3<Type> &start, const Point3<Type> &end) : Vector<Type, 3>(start, end) { this->initProperties(); };

        template <size_t oDim = 3>
        explicit Vector3(const Vector<Type, oDim> &vector);
        explicit Vector3(const Vector2<Type> &vector) : Vector<Type, 3>(vector) { this->initProperties(); };
        Vector3(const Vector3<Type> &vector) : Vector<Type, 3>(vector) { this->initProperties(); };

        template <size_t oDim = 3>
        Vector3<Type> &operator = (const Vector<Type, oDim> &vector);
        Vector3<Type> &operator = (const Vector2<Type> &vector);
        Vector3<Type> &operator = (const Vector3<Type> &vector);

        Vector3<Type> &normalise(void);
        Vector3<Type> normalised(void) const;

        Property<Vector3, Type> x;
        Property<Vector3, Type> y;
        Property<Vector3, Type> z;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        void setZ(const Type &value) { (*this)[2] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };
        const Type &getZ(void) const { return (*this)[2]; };

        Point3<Type> operator + (const Point3<Type> &point) const;

        Vector3<Type> operator + (const Vector3<Type> &vector) const;
        Vector3<Type> operator - (const Vector3<Type> &vector) const;
        Vector3<Type> operator - (void) const;
        Vector3<Type> operator * (const Vector3<Type> &vector) const;
        template <typename Other>
        Vector3<Type> operator * (const Other &value) const;
        template <typename Other>
        Vector3<Type> operator / (const Other &value) const;

        Vector3<Type> &operator += (const Vector3<Type> &vector);
        Vector3<Type> &operator -= (const Vector3<Type> &vector);
        Vector3<Type> &operator *= (const Vector3<Type> &vector);
        template <typename Other>
        Vector3<Type> &operator *= (const Other &value);
        template <typename Other>
        Vector3<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Vector3<Type> &vector);

template <typename Type>
Vector3<Type> operator < (const Point3<Type> &end, const Point3<Type> &start);

template <typename Type>
Vector3<Type> operator > (const Point3<Type> &start, const Point3<Type> &end);

template <typename Type, typename Other>
Vector3<Type> operator * (const Other &value, const Vector3<Type> &vector)
{ return vector * value; }

template <typename Type>
Point3<Type> operator + (const Point3<Type> &point, const Vector3<Type> &vector)
{ return vector + point; }

template <typename VectorType>
VectorType interpolate(const VectorType &vector1, const VectorType &vector2,
                       const double t);

class DivisionByZeroVectorException: public BaseException
{
    public:
        DivisionByZeroVectorException(void) = default;
        DivisionByZeroVectorException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Attempt to divide vector by 0")
            : BaseException(filename, line, function, message) {};
        ~DivisionByZeroVectorException(void) = default;
};

#include "vector.hpp"

#endif

