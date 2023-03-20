#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "base_exception.h"
#include "point.h"

template <typename Type>
class Texture
{
    public:
        virtual ~Texture(void) = 0;
        virtual Type getAt(const Point2<double> &point) const = 0;

    protected:
        void check_bounding(const Point2<double> &point) const;
};

class CommonTextureException: public BaseException
{
    public:
        CommonTextureException(void) = default;
        CommonTextureException(const char *filename, const size_t line,
                               const char *function,
                               const char *message = "General texture exception")
            : BaseException(filename, line, function, message) {};
        ~CommonTextureException(void) = default;
};

class OutOfBoundTextureException: public CommonTextureException
{
    public:
        OutOfBoundTextureException(void) = default;
        OutOfBoundTextureException(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = "Given texture coordinate is out of bounds")
            : CommonTextureException(filename, line, function, message) {};
        ~OutOfBoundTextureException(void) = default;
};

#include "texture.hpp"

#endif

