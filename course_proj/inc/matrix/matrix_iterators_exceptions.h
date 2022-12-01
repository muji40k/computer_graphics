#ifndef _MATRIX_ITERATORS_EXCEPTIONS_H_
#define _MATRIX_ITERATORS_EXCEPTIONS_H_

#include "base_exception.h"

class ErrorMatrixIteratorNullPointer : public BaseException
{
    public:
        ErrorMatrixIteratorNullPointer(void) = delete;
        ErrorMatrixIteratorNullPointer(const char *filename, 
                                          const size_t line,
                                          const char *function,
                                          const char *message = \
                                          "Unexpected null pointer\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixIteratorNullPointer(void) = default;
};

class ErrorMatrixIteratorExpired : public BaseException
{
    public:
        ErrorMatrixIteratorExpired(void) = delete;
        ErrorMatrixIteratorExpired(const char *filename,
                                      const size_t line,
                                      const char *function,
                                      const char *message = \
                                      "Iterable object has already expired\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixIteratorExpired(void) = default;
};

class ErrorMatrixIteratorLimitViolation : public BaseException
{
    public:
        ErrorMatrixIteratorLimitViolation(void) = delete;
        ErrorMatrixIteratorLimitViolation(const char *filename,
                                             const size_t line,
                                             const char *function,
                                             const char *message = \
                                             "Attempt to escape iterable " \
                                             "range\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixIteratorLimitViolation(void) = default;
};

#endif

