#include "split_display_decorator.h"

SplitDisplayDecorator::SplitDisplayDecorator(BaseDisplayAdapter &parent,
                                             const size_t x, const size_t y,
                                             const size_t width,
                                             const size_t height)
    : parent(parent)
{
    if (x + width > parent.width() || y + height > parent.height())
        throw CALL_EX(SizeViolationSplitDisplayException);

    double pwidth = parent.realWidth() / (parent.width() - 1),
           pheight = parent.realHeight() / (parent.height() - 1);

    this->setOffset(parent.offsetX() + x * pwidth,
                    parent.offsetY() - y * pheight);

    this->split_x = x;
    this->split_y = y;
    this->split_width = width;
    this->split_height = height;

    this->setRealWidth((width - 1) * pwidth);
}

SplitDisplayDecorator::~SplitDisplayDecorator(void) {}

size_t SplitDisplayDecorator::width(void) const { return this->split_width; }
size_t SplitDisplayDecorator::height(void) const { return this->split_height; }

void SplitDisplayDecorator::setAt(size_t i, size_t j, const Intensity<> &intensity)
{
    this->parent.setAt(this->split_x + i, this->split_y + j, intensity);
}

