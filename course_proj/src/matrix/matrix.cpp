#include "matrix.h"

template <>
Matrix<double> &Matrix<double>::inverse(void)
{
    if (this->isEmpty())
        throw ErrorMatrixEmpty(__FILE__, __LINE__, __FUNCTION__);

    if (this->size != this->row_size)
        throw ErrorMatrixNonSquare(__FILE__, __LINE__, __FUNCTION__);

    double det = this->determinant();

    if (EPS > fabs(det))
        throw ErrorMatrixNoInverted(__FILE__, __LINE__, __FUNCTION__);

    Matrix<double> copy;
    std::shared_ptr<MatrixRow<double>[]> out = Matrix<double>::allocate_matrix(this->size,
                                                                               this->row_size);

    for (size_t i = 0; this->size > i; i++)
        for (size_t j = 0; this->row_size > j; j++)
        {
            copy = *this;

            copy.removeColumn(j);
            copy.removeRow(i);

            out[j][i] = copy.determinant() / det;

            if (1 == (i + j) % 2)
                out[j][i] *= -1;
        }

    this->data = out;

    return *this;
}

template <>
size_t Matrix<double>::descendingGauss(void)
{
    Matrix<double> copy (*this), out (1, this->getColumns());
    size_t swaps = 0;

    size_t i = 0, k = 0;

    do
    {
        for (; k < copy.size && EPS > fabs(copy[k][0]); k++);

        if (copy.size == k)
            throw ErrorMatrixNoSolution(__FILE__, __LINE__, __FUNCTION__);

        if (0 != k)
        {
            copy.swapRows(0, k);
            swaps++;
        }

        for (size_t j = 1; copy.size > j; j++)
            copy[j] -= copy[j][0] / copy[0][0] * copy[0];

        for (size_t j = i; this->row_size > j; j++)
            out[i][j] = copy[0][j - i];

        try
        {
            copy.removeColumn(0);
            copy.removeRow(0);
            out.appendRow();
        }
        catch (const ErrorMatrixEmpty &er)
        {
        }

        i++;
        k = 0;
    }
    while (this->size > i);

    this->data = out.data;

    return swaps;
}

