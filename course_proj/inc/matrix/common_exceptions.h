#ifndef _COMMON_EXCEPTIONS_H_
#define _COMMON_EXCEPTIONS_H_

#include "base_exception.h"

class ErrorDivisionByZero : public BaseException
{
    public:
        ErrorDivisionByZero(void) = delete;
        ErrorDivisionByZero(const char *filename, const size_t line,
                            const char *function,
                            const char *message = \
                            "Division by zero\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorDivisionByZero(void) = default;
};

#endif

