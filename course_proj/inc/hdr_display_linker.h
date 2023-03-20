#ifndef _HDR_DISPLAY_LINKER_H_
#define _HDR_DISPLAY_LINKER_H_

#include <memory>

#include "base_display_adapter.h"
#include "matrix_display_adapter.h"
#include "display_transform_strategy.h"

class HDRDisplayLinker
{
    public:
        HDRDisplayLinker(BaseDisplayAdapter &adapter);
        BaseDisplayAdapter &getHDRAdapter(void);
        void apply(const DisplayTransformStrategy &strategy);

    private:
        BaseDisplayAdapter &adapter;
        std::shared_ptr<MatrixDisplayAdapter> madapter;
        std::shared_ptr<Matrix<Intensity<>>> matrix;
};

#endif

