#include "qt_display_adapter.h"
#include <QColor>

QtDisplayAdapter::QtDisplayAdapter(QImage &image) : image(image) {}

QtDisplayAdapter::~QtDisplayAdapter(void) {}

size_t QtDisplayAdapter::width(void) const
{
    return this->image.width();
}

size_t QtDisplayAdapter::height(void) const
{
    return this->image.height();
}

void QtDisplayAdapter::setAt(size_t i, size_t j, const Intensity<> &intensity)
{
    if (i >= this->width() || j >= this->height())
        throw CALL_EX(IndexViolationQtDisplayException);

    Intensity<> cint = intensity;

    for (size_t i = 0; cint.size() > i; i++)
    {
        if (255 < cint[i])
            cint[i] = 255;

        // cint[i] *= 255;
    }

    this->image.setPixelColor(i, j, QColor(cint[0], cint[1], cint[2]));
}

