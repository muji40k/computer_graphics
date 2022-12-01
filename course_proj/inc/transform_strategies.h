#ifndef _TRANSFORM_STRATEGIES_H_
#define _TRANSFORM_STRATEGIES_H_

#include "transform.h"

template <typename Type, size_t nDim = 3>
class MoveStrategy : public BaseTransformStrategy<Type, nDim>
{
    public:
        MoveStrategy(const std::initializer_list<Type> &list);
};

template <typename Type, size_t nDim = 3>
class ScaleStrategy : public BaseTransformStrategy<Type, nDim>
{
    public:
        ScaleStrategy(const std::initializer_list<Type> &list);
};

template <typename Type>
class RotateStrategyOX : public BaseTransformStrategy<Type, 3>
{
    public:
        RotateStrategyOX(const double &angle);
};

template <typename Type>
class RotateStrategyOY : public BaseTransformStrategy<Type, 3>
{
    public:
        RotateStrategyOY(const double &angle);
};

template <typename Type>
class RotateStrategyOZ : public BaseTransformStrategy<Type, 3>
{
    public:
        RotateStrategyOZ(const double &angle);
};

#include "basis.h"

template <typename Type, size_t nDim = 3>
class BasisStrategy : public BaseTransformStrategy<Type, nDim>
{
    public:
        BasisStrategy(const Basis<Type, nDim> &basis);
};

#include "transform_strategies.hpp"

#endif

