#ifndef _BASIS_H_
#define _BASIS_H_

#include <iostream>
#include <initializer_list>

#include "property.h"
#include "base_exception.h"

#include "transform.h"
#include "point.h"
#include "vector.h"

template <typename Type, size_t nDim = 3>
class Basis : public Transformable<Type, nDim>
{
    public:
        Basis(void);
        template <size_t oDim = nDim>
        Basis(const Basis<Type, oDim> &basis);
        template <size_t oDim = nDim>
        Basis(Basis<Type, oDim> &&basis);
        Basis(const std::initializer_list<const Vector<Type, nDim>> &list,
              const Point<Type, nDim> &center = Point<Type, nDim>());

        template <size_t oDim = nDim>
        Basis<Type, nDim> &operator = (const Basis<Type, oDim> &basis);

        bool operator == (const Basis<Type, nDim> &basis);
        bool operator != (const Basis<Type, nDim> &basis);

        void setCenter(const Point<Type, nDim> &point);
        Point<Type, nDim> getCenter(void) const;

        template <size_t oDim = nDim>
        void setVector(const Vector<Type, oDim> &vector, const size_t index);
        Vector<Type, nDim> getVector(const size_t index) const;

        void orthogonalize(void);

        virtual void apply(const Transform<Type, nDim> &transform) override;
        virtual void undo(const Transform<Type, nDim> &transform) override;

    protected:
        template <size_t oDim = nDim>
        void directSetVector(const Vector<Type, oDim> &vector,
                             const size_t index);

    private:
        Point<Type, nDim> _center = Point<Type, nDim>();
        Vector<Type, nDim> _axis[nDim] = { Vector<Type, nDim>() };

        static void _orthogonalize(Vector<Type, nDim>(&arr)[nDim]);
        static bool isDegenerate(const Vector<Type, nDim>(&arr)[nDim]);
};

template <typename Type, size_t nDim = 3>
std::ostream& operator << (std::ostream &stream, const Basis<Type, nDim> &basis);

template <typename Type>
class Basis3;

template <typename Type>
class Basis2 : public Basis<Type, 2>
{
    private:
        void initProperties(void);

    public:
        Basis2(void) : Basis<Type, 2>() { this->checkLeft(); };
        template <size_t oDim = 2>
        Basis2(const Basis<Type, oDim> &basis)
            : Basis<Type, 2>(basis) { this->checkLeft(); }
        Basis2(const Basis2<Type> &basis)
            : Basis<Type, 2>(basis), _left(basis.isLeft()) {};
        Basis2(const Basis3<Type> &basis)
            : Basis<Type, 2>(basis), _left(basis.isLeft()) {};
        Basis2(Basis2<Type> &&basis)
            : Basis<Type, 2>(basis), _left(basis.isLeft()) {};
        Basis2(const Point<Type, 2> &center, const Vector<Type, 2> &x,
               const Vector<Type, 2> &y, const Vector<Type, 2> &z)
            : Basis<Type, 2>({x, y, z}, center) { this->checkLeft(); };
        Basis2(const Point2<Type> &center, const Vector2<Type> &x,
               const Vector2<Type> &y, const Vector2<Type> &z)
            : Basis<Type, 2>({x, y, z}, center) { this->checkLeft(); };
        Basis2(const std::initializer_list<const Vector<Type, 2>> &list,
               const Point<Type, 2> &center = Point<Type, 2>())
            : Basis<Type, 2>(list, center) { this->checkLeft(); };

        template <size_t oDim = 2>
        Basis2<Type> &operator = (const Basis<Type, oDim> &basis)
        { static_cast<Basis<Type, 2> &>(*this) = basis; this->checkLeft(); return *this; }
        Basis2<Type> &operator = (const Basis2<Type> &basis)
        { static_cast<Basis<Type, 2> &>(*this) = basis; this->left(basis.isLeft()); return *this; }
        Basis2<Type> &operator = (const Basis3<Type> &basis)
        { static_cast<Basis<Type, 2> &>(*this) = basis; this->left(basis.isLeft()); return *this; }

        Point2<Type> getCenter(void) const
        { return Point2<Type>(this->Basis<Type, 2>::getCenter()); }

        template <size_t oDim = 2>
        void setVector(const Vector<Type, oDim> &vector, const size_t index)
        { this->Basis<Type, 2>::setVector(vector, index); this->checkLeft(); }
        Vector2<Type> getVector(const size_t index) const
        { return Vector2<Type>(this->Basis<Type, 2>::getVector(index)); }

        void orthogonalize(void)
        { this->Basis<Type, 2>::orthogonalize(); this->checkLeft(); }

        bool isLeft(void)
        { return this->_left; }
        void left(bool mark)
        { this->_left = mark; this->orthogonalize(); }

        virtual void apply(const Transform<Type, 2> &transform) override
        { this->Basis<Type, 2>::apply(transform); this->checkLeft(); }
        virtual void undo(const Transform<Type, 2> &transform) override
        { this->Basis<Type, 2>::undo(transform); this->checkLeft(); }

    private:
        bool _left = true;

        void checkLeft(void);
};

template <typename Type>
std::ostream& operator << (std::ostream &stream, const Basis2<Type> &basis);

template <typename Type>
class Basis3 : public Basis<Type, 3>
{
    public:
        Basis3(void) : Basis<Type, 3>() { this->checkLeft(); };
        template <size_t oDim = 3>
        Basis3(const Basis<Type, oDim> &basis)
            : Basis<Type, 3>(basis) { this->checkLeft(); }
        Basis3(const Basis2<Type> &basis)
            : Basis<Type, 3>(basis), _left(basis.isLeft()) {};
        Basis3(const Basis3<Type> &basis)
            : Basis<Type, 3>(basis), _left(basis.isLeft()) {};
        Basis3(Basis3<Type> &&basis)
            : Basis<Type, 3>(basis), _left(basis.isLeft()) {};
        Basis3(const Point<Type, 3> &center, const Vector<Type, 3> &x,
               const Vector<Type, 3> &y, const Vector<Type, 3> &z)
            : Basis<Type, 3>({x, y, z}, center) { this->checkLeft(); };
        Basis3(const Point3<Type> &center, const Vector3<Type> &x,
               const Vector3<Type> &y, const Vector3<Type> &z)
            : Basis<Type, 3>({x, y, z}, center) { this->checkLeft(); };
        Basis3(const std::initializer_list<const Vector<Type, 3>> &list,
               const Point<Type, 3> &center = Point<Type, 3>())
            : Basis<Type, 3>(list, center) { this->checkLeft(); };

        template <size_t oDim = 3>
        Basis3<Type> &operator = (const Basis<Type, oDim> &basis)
        { static_cast<Basis<Type, 3> &>(*this) = basis; this->checkLeft(); return *this; }
        Basis3<Type> &operator = (const Basis2<Type> &basis)
        { static_cast<Basis<Type, 3> &>(*this) = basis; this->left(basis.isLeft()); return *this; }
        Basis3<Type> &operator = (const Basis3<Type> &basis)
        { static_cast<Basis<Type, 3> &>(*this) = basis; this->left(basis.isLeft()); return *this; }

        Point3<Type> getCenter(void) const
        { return Point3<Type>(this->Basis<Type, 3>::getCenter()); }

        template <size_t oDim = 3>
        void setVector(const Vector<Type, oDim> &vector, const size_t index)
        { this->Basis<Type, 3>::setVector(vector, index); this->checkLeft(); }
        Vector3<Type> getVector(const size_t index) const
        { return Vector3<Type>(this->Basis<Type, 3>::getVector(index)); }

        void orthogonalize(void)
        { this->Basis<Type, 3>::orthogonalize(); this->checkLeft(); }

        bool isLeft(void)
        { return this->_left; }
        void left(bool mark)
        { this->_left = mark; this->orthogonalize(); }

        virtual void apply(const Transform<Type, 3> &transform) override
        { this->Basis<Type, 3>::apply(transform); this->checkLeft(); }
        virtual void undo(const Transform<Type, 3> &transform) override
        { this->Basis<Type, 3>::undo(transform); this->checkLeft(); }

    private:
        bool _left = true;

        void checkLeft(void);
};

template <typename Type>
std::ostream& operator << (std::ostream &stream, const Basis3<Type> &basis);

class DegenrateBasisException: public BaseException
{
    public:
        DegenrateBasisException(void) = default;
        DegenrateBasisException(const char *filename, const size_t line,
                                const char *function,
                                const char *message = "Given basis is degenerate")
            : BaseException(filename, line, function, message) {};
        ~DegenrateBasisException(void) = default;
};

class NullBasisException: public BaseException
{
    public:
        NullBasisException(void) = default;
        NullBasisException(const char *filename, const size_t line,
                           const char *function,
                           const char *message = "Basis contains null vector")
            : BaseException(filename, line, function, message) {};
        ~NullBasisException(void) = default;
};

class IndexViolationBasisException: public BaseException
{
    public:
        IndexViolationBasisException(void) = default;
        IndexViolationBasisException(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = "Basis vector index violation")
            : BaseException(filename, line, function, message) {};
        ~IndexViolationBasisException(void) = default;
};

#include "basis.hpp"

#endif

