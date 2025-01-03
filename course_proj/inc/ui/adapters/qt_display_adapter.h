#ifndef _QT_DISPLAY_ADAPTER_H_
#define _QT_DISPLAY_ADAPTER_H_

#include <QImage>

#include "base_display_adapter.h"

#include "base_exception.h"

class QtDisplayAdapter : public BaseDisplayAdapter
{
    public:
        QtDisplayAdapter(QImage &image);
        virtual ~QtDisplayAdapter(void) override;
        virtual size_t width(void) const override;
        virtual size_t height(void) const override;
        virtual void setAt(size_t i, size_t j, const Intensity<> &intensity) override;

    private:
        QImage &image;
};

#endif

