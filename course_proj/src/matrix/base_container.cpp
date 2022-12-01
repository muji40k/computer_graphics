#include "base_container.h"

bool BaseContainer::isEmpty(void) const
{
    return 0 == this->size;
}

size_t BaseContainer::getSize(void) const
{
    return this->size;
}

