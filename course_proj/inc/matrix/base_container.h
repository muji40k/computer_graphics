#ifndef _BASE_CONTAINER_H_
#define _BASE_CONTAINER_H_

#include <cstdlib>

class BaseContainer
{
    public:
        BaseContainer(void) = default;
        virtual ~BaseContainer(void) = default;
        virtual bool isEmpty(void) const;
        virtual size_t getSize(void) const;
    protected:
        size_t size;
};

#endif

