#ifndef _EMPTY_DISPLAY_ADAPTER_H_
#define _EMPTY_DISPLAY_ADAPTER_H_

#include "base_display_adapter.h"

class EmptyDisplayAdapter : public BaseDisplayAdapter
{
    public:
        EmptyDisplayAdapter(size_t w, size_t h);
        virtual ~EmptyDisplayAdapter(void) override;
        virtual size_t width(void) const override;
        virtual size_t height(void) const override;
        virtual void setAt(size_t i, size_t j, const Intensity<> &intensity) override;

    private:
        size_t w;
        size_t h;
};

#endif

