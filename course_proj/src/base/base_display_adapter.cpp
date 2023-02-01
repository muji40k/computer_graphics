#include "base_display_adapter.h"
#include <float.h>

BaseDisplayAdapter::~BaseDisplayAdapter(void) {}

double BaseDisplayAdapter::realWidth(void) const
{
    return this->real_width;
}

double BaseDisplayAdapter::realHeight(void) const
{
    return this->real_height;
}

void BaseDisplayAdapter::setRealWidth(const double width)
{
    if (0 >= width)
        throw CALL_EX(NegativeSizeDisplayAdapterException);

    double aspect = (double)this->height() / this->width();

    this->real_width = width;
    this->real_height = width * aspect;
}

void BaseDisplayAdapter::setRealHeight(const double height)
{
    if (0 >= height)
        throw CALL_EX(NegativeSizeDisplayAdapterException);

    double aspect = (double)this->width() / this->height();

    this->real_height = height;
    this->real_width = height * aspect;
}

double BaseDisplayAdapter::offsetX(void) const
{
    return this->offset_x;
}

double BaseDisplayAdapter::offsetY(void) const
{
    return this->offset_y;
}

void BaseDisplayAdapter::setOffsetX(const double x)
{
    this->offset_x = x;
}

void BaseDisplayAdapter::setOffsetY(const double y)
{
    this->offset_y = y;
}

void BaseDisplayAdapter::setOffset(const double x, const double y)
{
    this->offset_x = x;
    this->offset_y = y;
}

