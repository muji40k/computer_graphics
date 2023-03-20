#include "array_texture.h"

template <typename Type>
ArrayTexture<Type>::ArrayTexture(const Matrix<Type> &matrix)
{
    this->matrix = std::make_shared<Matrix<Type>>(matrix);
}

template <typename Type>
ArrayTexture<Type>::~ArrayTexture(void) {}

template <typename Type>
Type ArrayTexture<Type>::getAt(const Point2<double> &point) const
{
    this->check_bounding(point);

    double su = (this->matrix->getColumns() - 1) * point.x;
    double sv = (this->matrix->getRows() - 1) * (1 - point.y);

    double tmp;
    size_t isu = su, isv = sv;
    double fsu = modf(su, &tmp), fsv = modf(sv, &tmp);

    Type out;

    if (this->matrix->getColumns() == isu + 1
        && this->matrix->getRows() == isv + 1)
        out = (*this->matrix)[isv][isu];
    else if (this->matrix->getColumns() == isu + 1)
        out = (*this->matrix)[isv][isu] * (1 - fsv) \
              + (*this->matrix)[isv + 1][isu] * fsv;
    else if (this->matrix->getRows() == isv + 1)
        out = (*this->matrix)[isv][isu] * (1 - fsu) \
              + (*this->matrix)[isv][isu + 1] * fsu;
    else
    {
        Type dx1 = (*this->matrix)[isv][isu] * (1 - fsu) \
                   + (*this->matrix)[isv][isu + 1] * fsu,
             dx2 = (*this->matrix)[isv + 1][isu] * (1 - fsu) \
                   + (*this->matrix)[isv + 1][isu + 1] * fsu;
        out = dx1 * (1 - fsv) + dx2 * fsv;
    }

    return out;
}

