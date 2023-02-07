#ifndef _TRANSFORM_STRATEGIES_HPP_
#define _TRANSFORM_STRATEGIES_HPP_

#include "transform_strategies.h"

#include <iterator>
#include <cmath>

template <typename Type, size_t nDim>
MoveStrategy<Type, nDim>::MoveStrategy(const std::initializer_list<Type> &list)
    : BaseTransformStrategy<Type, nDim>()
{
    size_t limit = list.size();

    if (nDim < limit)
        limit = nDim;

    auto it = list.begin();

    for (size_t i = 0; limit > i; i++, it++)
    {
        this->matrix[nDim][i] = *it;
        this->inverse[nDim][i] = -(*it);
    }
}

template <typename Type, size_t nDim>
ScaleStrategy<Type, nDim>::ScaleStrategy(const std::initializer_list<Type> &list)
    : BaseTransformStrategy<Type, nDim>()
{
    size_t limit = list.size();

    if (nDim < limit)
        limit = nDim;

    auto it = list.begin();

    for (size_t i = 0; limit > i; i++, it++)
    {
        this->matrix[i][i] = *it;
        this->inverse[i][i] = 1 / (*it);
    }
}

template <typename Type>
RotateStrategyOX<Type>::RotateStrategyOX(const double &angle)
    : BaseTransformStrategy<Type, 3>()
{
    double s = sin(angle), c = cos(angle);
    this->matrix[1][1] = this->inverse[1][1] = c;
    this->matrix[2][2] = this->inverse[2][2] = c;
    this->matrix[2][1] = -(this->inverse[2][1] = s);
    this->matrix[1][2] = -(this->inverse[1][2] = -s);
}

template <typename Type>
RotateStrategyOY<Type>::RotateStrategyOY(const double &angle)
    : BaseTransformStrategy<Type, 3>()
{
    double s = sin(angle), c = cos(angle);
    this->matrix[2][2] = this->inverse[2][2] = c;
    this->matrix[0][0] = this->inverse[0][0] = c;
    this->matrix[0][2] = -(this->inverse[0][2] = s);
    this->matrix[2][0] = -(this->inverse[2][0] = -s);
}

template <typename Type>
RotateStrategyOZ<Type>::RotateStrategyOZ(const double &angle)
    : BaseTransformStrategy<Type, 3>()
{
    double s = sin(angle), c = cos(angle);
    this->matrix[0][0] = this->inverse[0][0] = c;
    this->matrix[1][1] = this->inverse[1][1] = c;
    this->matrix[1][0] = -(this->inverse[1][0] = s);
    this->matrix[0][1] = -(this->inverse[0][1] = -s);
}

template <typename Type, size_t nDim>
BasisStrategy<Type, nDim>::BasisStrategy(const Basis<Type, nDim> &basis)
    : BaseTransformStrategy<Type, nDim>()
{
    Matrix<Type> tmp (nDim + 1, nDim + 1);
    tmp[nDim][nDim] = Type(1);

    for (size_t i = 0; nDim > i; i++)
    {
        for (size_t j = 0; nDim > j; j++)
            tmp[i][j] = basis.getVector(i)[j];

        this->matrix[nDim][i] = basis.getCenter()[i];
    }

    this->matrix = tmp * this->matrix;
    this->inverse = this->matrix.getInversed();
}

#endif

