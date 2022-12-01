#ifndef _MATRIX_ROW_ITERATORS_EXCEPTIONS_H_
#define _MATRIX_ROW_ITERATORS_EXCEPTIONS_H_

#include "base_exception.h"

class ErrorMatrixRowIteratorNullPointer : public BaseException
{
    public:
        ErrorMatrixRowIteratorNullPointer(void) = delete;
        ErrorMatrixRowIteratorNullPointer(const char *filename, 
                                          const size_t line,
                                          const char *function,
                                          const char *message = \
                                          "Unexpected null pointer\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowIteratorNullPointer(void) = default;
};

class ErrorMatrixRowIteratorExpired : public BaseException
{
    public:
        ErrorMatrixRowIteratorExpired(void) = delete;
        ErrorMatrixRowIteratorExpired(const char *filename,
                                      const size_t line,
                                      const char *function,
                                      const char *message = \
                                      "Iterable object has already expired\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowIteratorExpired(void) = default;
};

class ErrorMatrixRowIteratorLimitViolation : public BaseException
{
    public:
        ErrorMatrixRowIteratorLimitViolation(void) = delete;
        ErrorMatrixRowIteratorLimitViolation(const char *filename,
                                             const size_t line,
                                             const char *function,
                                             const char *message = \
                                             "Attempt to escape iterable " \
                                             "range\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowIteratorLimitViolation(void) = default;
};

#endif

