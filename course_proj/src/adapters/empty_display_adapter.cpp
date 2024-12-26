#include "empty_display_adapter.h"

EmptyDisplayAdapter::EmptyDisplayAdapter(size_t w, size_t h)
    : w(w), h(h) {}

EmptyDisplayAdapter::~EmptyDisplayAdapter(void) {}

size_t EmptyDisplayAdapter::width(void) const
{
    return this->w;
}

size_t EmptyDisplayAdapter::height(void) const
{
    return this->h;
}

void EmptyDisplayAdapter::setAt(size_t, size_t, const Intensity<> &) {}

