#ifndef _BASE_DISPLAY_ADAPTER_H_
#define _BASE_DISPLAY_ADAPTER_H_

#include <cstdlib>

#include "base_exception.h"

#include "intensity.h"

class BaseDisplayAdapter
{
    public:
        virtual ~BaseDisplayAdapter(void) = 0;
        virtual size_t width(void) const = 0;
        virtual size_t height(void) const = 0;
        virtual void setAt(size_t i, size_t j, const Intensity<> &intensity) = 0;

        double realWidth(void) const;
        double realHeight(void) const;
        void setRealWidth(const double width);
        void setRealHeight(const double height);

        double offsetX(void) const;
        double offsetY(void) const;
        void setOffsetX(const double x);
        void setOffsetY(const double y);
        void setOffset(const double x, const double y);

    private:
        double offset_x = 0;
        double offset_y = 0;
        double real_width = 0;
        double real_height = 0;
};

DEF_EX(CommonDisplayAdapterException, BaseException,
       "General display adapter exception");
DEF_EX(NegativeSizeDisplayAdapterException, CommonDisplayAdapterException,
       "Given display size is negative");
DEF_EX(IndexViolationDisplayAdapterException, CommonDisplayAdapterException,
       "Index out of display range");

#endif

