#include "matrix_row.h"

template <>
bool MatrixRow<double>::isEqual(const MatrixRow<double> &row) const
{
    if (this->isEmpty() || row.isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != row.size)
        return false;

    bool same = true;

    for (size_t i = 0; same && this->size > i; i++)
        same = (EPS > fabs((*this)[i] - row[i]));

    return same;
}

template <>
MatrixRow<double> &MatrixRow<double>::operator /= (const double &data)
{
    if (this->isEmpty())
        throw ErrorMatrixRowEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (EPS > fabs(data))
        throw ErrorDivisionByZero(__FILE__, __LINE__, __FUNCTION__);

    for (size_t i = 0; this->size > i; i++)
        (*this)[i] /= data;

    return *this;
}


