#include "renderer.h"

RenderProgress::RenderProgress(const BaseDisplayAdapter &adapter)
{
    this->max = adapter.width() * adapter.height();
    this->current = 0;
}

void RenderProgress::clear(void)
{
    this->current = 0;
}

double RenderProgress::progress(void) const
{
    return (double)this->current / this->max;
}

void RenderProgress::step(void)
{
    this->mutex.lock();
    this->current++;
    this->mutex.unlock();
}

Renderer::~Renderer(void) {}

