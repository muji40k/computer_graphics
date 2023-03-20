#include "hdr_display_linker.h"


HDRDisplayLinker::HDRDisplayLinker(BaseDisplayAdapter &adapter)
    : adapter(adapter)
{
    this->matrix = std::make_shared<Matrix<Intensity<>>>(adapter.height(),
                                                         adapter.width());
    this->madapter = std::make_shared<MatrixDisplayAdapter>(*this->matrix);


    this->madapter->setOffset(adapter.offsetX(), adapter.offsetY());
    this->madapter->setRealWidth(adapter.realWidth());
}

BaseDisplayAdapter &HDRDisplayLinker::getHDRAdapter(void)
{
    return *this->madapter;
}

void HDRDisplayLinker::apply(const DisplayTransformStrategy &strategy)
{
    strategy.transform(*this->matrix, this->adapter);
}

