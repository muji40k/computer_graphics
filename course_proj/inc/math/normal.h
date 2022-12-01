#ifndef _NORMAL_H_
#define _NORMAL_H_

#include <iostream>
#include <cstddef>
#include <initializer_list>

#include "property.h"
#include "base_exception.h"

#include "transform.h"
#include "point.h"
#include "vector.h"

template <typename Type, size_t nDim = 3>
class Normal : public Vector<Type, nDim>
{
    public:
        Normal(void) : Vector<Type, nDim>() {};
        template <size_t oDim = nDim>
        Normal(const Vector<Type, oDim> &vector) : Vector<Type, nDim>(vector) {}
        template <size_t oDim = nDim>
        Normal(const Normal<Type, oDim> &normal) : Vector<Type, nDim>(normal) {}
        explicit Normal(const std::initializer_list<Type> &list) : Vector<Type, nDim>(list) {};

        Normal(const Point<Type, nDim> &start, const Point<Type, nDim> &end) : Vector<Type, nDim>(start, end) {};

        template <size_t oDim = 2>
        Normal<Type, nDim> &operator = (const Vector<Type, oDim> &vector);
        template <size_t oDim = 2>
        Normal<Type, nDim> &operator = (const Normal<Type, oDim> &normal);

        Normal<Type, nDim> &normalise(void);
        Normal<Type, nDim> normalised(void) const;

        Normal<Type, nDim> operator + (const Vector<Type, nDim> &vector) const;
        Normal<Type, nDim> operator - (const Vector<Type, nDim> &vector) const;
        Normal<Type, nDim> operator + (const Normal<Type, nDim> &normal) const;
        Normal<Type, nDim> operator - (const Normal<Type, nDim> &normal) const;
        Normal<Type, nDim> operator - (void) const;
        template <typename Other>
        Normal<Type, nDim> operator * (const Other &value) const;
        template <typename Other>
        Normal<Type, nDim> operator / (const Other &value) const;

        Normal<Type, nDim> &operator += (const Vector<Type, nDim> &vector);
        Normal<Type, nDim> &operator -= (const Vector<Type, nDim> &vector);
        Normal<Type, nDim> &operator += (const Normal<Type, nDim> &normal);
        Normal<Type, nDim> &operator -= (const Normal<Type, nDim> &normal);
        template <typename Other>
        Normal<Type, nDim> &operator *= (const Other &value);
        template <typename Other>
        Normal<Type, nDim> &operator /= (const Other &value);

        virtual void apply(const Transform<Type, nDim> &transform) override;
        virtual void undo(const Transform<Type, nDim> &transform) override;
};

template <typename Type, size_t nDim>
std::ostream& operator << (std::ostream& stream, const Normal<Type, nDim> &normal);

template <typename Type, size_t nDim, typename Other>
Normal<Type, nDim> operator * (const Other &value, const Normal<Type, nDim> &normal)
{ return normal * value; }

template <typename Type, size_t nDim>
Point<Type, nDim> operator + (const Point<Type, nDim> &point,
                              const Normal<Type, nDim> &normal)
{ return normal + point; }

template <typename Type>
class Normal3;

template <typename Type>
class Normal2 : public Normal<Type, 2>
{
    private:
        void initProperties(void);

    public:
        Normal2(void) : Normal<Type, 2>() { this->initProperties(); };
        Normal2(const Type &x, const Type &y) : Normal<Type, 2>({x, y}) { this->initProperties(); };
        explicit Normal2(const std::initializer_list<Type> &list) : Normal<Type, 2>(list) { this->initProperties(); };

        Normal2(const Point2<Type> &start, const Point2<Type> &end) : Normal<Type, 2>(start, end) { this->initProperties(); };

        template <size_t oDim = 2>
        explicit Normal2(const Normal<Type, oDim> &normal) : Normal<Type, 2>(normal) { this->initProperties(); }
        template <size_t oDim = 2>
        explicit Normal2(const Vector<Type, oDim> &vector) : Normal<Type, 2>(vector) { this->initProperties(); }

        Normal2(const Normal2<Type> &normal) : Normal<Type, 2>(normal) { this->initProperties(); };
        explicit Normal2(const Normal3<Type> &normal) : Normal<Type, 2>(normal) { this->initProperties(); };
        Normal2(const Vector2<Type> &vector) : Normal<Type, 2>(vector) { this->initProperties(); };
        explicit Normal2(const Vector3<Type> &vector) : Normal<Type, 2>(vector) { this->initProperties(); };

        template <size_t oDim = 2>
        Normal2<Type> &operator = (const Normal<Type, oDim> &normal);
        Normal2<Type> &operator = (const Normal2<Type> &normal);
        Normal2<Type> &operator = (const Normal3<Type> &normal);

        template <size_t oDim = 2>
        Normal2<Type> &operator = (const Vector<Type, oDim> &vector);
        Normal2<Type> &operator = (const Vector2<Type> &vector);
        Normal2<Type> &operator = (const Vector3<Type> &vector);

        Normal2<Type> &normalise(void);
        Normal2<Type> normalised(void) const;

        Property<Normal2, Type> x;
        Property<Normal2, Type> y;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };

        Point2<Type> operator + (const Point2<Type> &point) const;

        Normal2<Type> operator + (const Normal2<Type> &normal) const;
        Normal2<Type> operator - (const Normal2<Type> &normal) const;
        Normal2<Type> operator + (const Vector2<Type> &vector) const;
        Normal2<Type> operator - (const Vector2<Type> &vector) const;
        Normal2<Type> operator - (void) const;
        template <typename Other>
        Normal2<Type> operator * (const Other &value) const;
        template <typename Other>
        Normal2<Type> operator / (const Other &value) const;

        Normal2<Type> &operator += (const Normal2<Type> &normal);
        Normal2<Type> &operator -= (const Normal2<Type> &normal);
        Normal2<Type> &operator += (const Vector2<Type> &vector);
        Normal2<Type> &operator -= (const Vector2<Type> &vector);
        template <typename Other>
        Normal2<Type> &operator *= (const Other &value);
        template <typename Other>
        Normal2<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Normal2<Type> &normal);

template <typename Type, typename Other>
Normal2<Type> operator * (const Other &value, const Normal2<Type> &normal)
{ return normal * value; }

template <typename Type>
Point2<Type> operator + (const Point2<Type> &point, const Normal2<Type> &normal)
{ return normal + point; }

template <typename Type>
class Normal3 : public Normal<Type, 3>
{
    private:
        void initProperties(void);

    public:
        Normal3(void) : Normal<Type, 3>() { this->initProperties(); };
        Normal3(const Type &x, const Type &y, const Type &z) : Normal<Type, 3>({x, y, z}) { this->initProperties(); };
        explicit Normal3(const std::initializer_list<Type> &list) : Normal<Type, 3>(list) { this->initProperties(); };

        Normal3(const Point3<Type> &start, const Point3<Type> &end) : Normal<Type, 3>(start, end) { this->initProperties(); };

        template <size_t oDim = 3>
        explicit Normal3(const Normal<Type, oDim> &normal) : Normal<Type, 3>(normal) { this->initProperties(); }
        template <size_t oDim = 3>
        explicit Normal3(const Vector<Type, oDim> &vector) : Normal<Type, 3>(vector) { this->initProperties(); }

        Normal3(const Normal2<Type> &normal) : Normal<Type, 3>(normal) { this->initProperties(); };
        explicit Normal3(const Normal3<Type> &normal) : Normal<Type, 3>(normal) { this->initProperties(); };
        Normal3(const Vector2<Type> &vector) : Normal<Type, 3>(vector) { this->initProperties(); };
        explicit Normal3(const Vector3<Type> &vector) : Normal<Type, 3>(vector) { this->initProperties(); };

        template <size_t oDim = 3>
        Normal3<Type> &operator = (const Normal<Type, oDim> &normal);
        Normal3<Type> &operator = (const Normal2<Type> &normal);
        Normal3<Type> &operator = (const Normal3<Type> &normal);

        template <size_t oDim = 3>
        Normal3<Type> &operator = (const Vector<Type, oDim> &vector);
        Normal3<Type> &operator = (const Vector2<Type> &vector);
        Normal3<Type> &operator = (const Vector3<Type> &vector);

        Normal3<Type> &normalise(void);
        Normal3<Type> normalised(void) const;

        Property<Normal3, Type> x;
        Property<Normal3, Type> y;
        Property<Normal3, Type> z;
        void setX(const Type &value) { (*this)[0] = value; };
        void setY(const Type &value) { (*this)[1] = value; };
        void setZ(const Type &value) { (*this)[2] = value; };
        const Type &getX(void) const { return (*this)[0]; };
        const Type &getY(void) const { return (*this)[1]; };
        const Type &getZ(void) const { return (*this)[2]; };

        Point3<Type> operator + (const Point3<Type> &point) const;

        Normal3<Type> operator + (const Normal3<Type> &normal) const;
        Normal3<Type> operator - (const Normal3<Type> &normal) const;
        Normal3<Type> operator + (const Vector3<Type> &vector) const;
        Normal3<Type> operator - (const Vector3<Type> &vector) const;
        Normal3<Type> operator - (void) const;
        template <typename Other>
        Normal3<Type> operator * (const Other &value) const;
        template <typename Other>
        Normal3<Type> operator / (const Other &value) const;

        Normal3<Type> &operator += (const Normal3<Type> &normal);
        Normal3<Type> &operator -= (const Normal3<Type> &normal);
        Normal3<Type> &operator += (const Vector3<Type> &vector);
        Normal3<Type> &operator -= (const Vector3<Type> &vector);
        template <typename Other>
        Normal3<Type> &operator *= (const Other &value);
        template <typename Other>
        Normal3<Type> &operator /= (const Other &value);
};

template <typename Type>
std::ostream& operator << (std::ostream& stream, const Normal3<Type> &normal);

template <typename Type, typename Other>
Normal3<Type> operator * (const Other &value, const Normal3<Type> &normal)
{ return normal * value; }

template <typename Type>
Point3<Type> operator + (const Point3<Type> &point, const Normal3<Type> &normal)
{ return normal + point; }

#include "normal.hpp"

#endif

