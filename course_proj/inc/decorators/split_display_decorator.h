#ifndef _SPLIT_DISPLAY_DECORATOR_H_
#define _SPLIT_DISPLAY_DECORATOR_H_

#include "base_display_adapter.h"
#include "base_exception.h"

class SplitDisplayDecorator : public BaseDisplayAdapter
{
    public:
        SplitDisplayDecorator(BaseDisplayAdapter &parent,
                              const size_t x, const size_t y,
                              const size_t width, const size_t height);

        virtual ~SplitDisplayDecorator(void) override;
        virtual size_t width(void) const override;
        virtual size_t height(void) const override;
        virtual void setAt(size_t i, size_t j, const Intensity<> &intensity) override;

    private:
        BaseDisplayAdapter &parent;
        size_t split_x;
        size_t split_y;
        size_t split_width;
        size_t split_height;
};

class SizeViolationSplitDisplayException: public BaseException
{
    public:
        SizeViolationSplitDisplayException(void) = default;
        SizeViolationSplitDisplayException(const char *filename, const size_t line,
                                           const char *function,
                                           const char *message = "Decorator is out of origin size")
            : BaseException(filename, line, function, message) {};
        ~SizeViolationSplitDisplayException(void) = default;
};

#endif

