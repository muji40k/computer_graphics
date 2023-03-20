#ifndef _MATRIX_DISPLAY_ADAPTER_H_
#define _MATRIX_DISPLAY_ADAPTER_H_

#include "base_display_adapter.h"
#include "matrix.h"

class MatrixDisplayAdapter : public BaseDisplayAdapter
{
    public:
        MatrixDisplayAdapter(Matrix<Intensity<>> &matrix);
        virtual ~MatrixDisplayAdapter(void) override;
        virtual size_t width(void) const override;
        virtual size_t height(void) const override;
        virtual void setAt(size_t i, size_t j, const Intensity<> &intensity) override;

    private:
        Matrix<Intensity<>> &matrix;
};

#endif

