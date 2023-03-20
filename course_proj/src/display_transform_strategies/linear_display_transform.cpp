#include "linear_display_transform.h"

LinearDisplayTransform::~LinearDisplayTransform(void) {}

void LinearDisplayTransform::transform(const Matrix<Intensity<>> &hdr,
                                       BaseDisplayAdapter &adapter) const
{
    double max_i = 0;

    for (auto row : hdr)
        for (auto item : row)
            for (size_t i = 0; item.size() > i; i++)
                if (item[i] > max_i)
                    max_i = item[i];

    max_i = (double)1 / max_i;

    for (size_t i = 0; adapter.width() > i; i++)
        for (size_t j = 0; adapter.height() > j; j++)
            adapter.setAt(i, j, hdr[j][i] * max_i);
}

