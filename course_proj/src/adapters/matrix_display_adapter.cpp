#include "matrix_display_adapter.h"

MatrixDisplayAdapter::MatrixDisplayAdapter(Matrix<Intensity<>> &matrix)
    : matrix(matrix) {}

MatrixDisplayAdapter::~MatrixDisplayAdapter(void) {}

size_t MatrixDisplayAdapter::width(void) const
{
    return this->matrix.getColumns();
}

size_t MatrixDisplayAdapter::height(void) const
{
    return this->matrix.getRows();
}

void MatrixDisplayAdapter::setAt(size_t i, size_t j, const Intensity<> &intensity)
{
    if (i >= this->width() || j >= this->height())
        throw CALL_EX(IndexViolationDisplayAdapterException);

    this->matrix[j][i] = intensity;
}

