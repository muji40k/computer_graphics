#include "gamma_display_transform.h"

GammaDisplayTransform::GammaDisplayTransform(double gamma)
    : igamma((double)1 / gamma) {}

GammaDisplayTransform::~GammaDisplayTransform(void) {}

void GammaDisplayTransform::transform(const Matrix<Intensity<>> &hdr,
                                       BaseDisplayAdapter &adapter) const
{
    Intensity<> tmp;

    for (size_t i = 0; adapter.width() > i; i++)
        for (size_t j = 0; adapter.height() > j; j++)
        {
            for (size_t k = 0; hdr[j][i].size() > k; k++)
                tmp[k] = pow(hdr[j][i][k], this->igamma);

            adapter.setAt(i, j, tmp);
        }
}
