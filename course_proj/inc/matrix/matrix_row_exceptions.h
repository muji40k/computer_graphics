#ifndef _MATRIX_ROW_EXCEPTIONS_H_
#define _MATRIX_ROW_EXCEPTIONS_H_

#include "base_exception.h"

class ErrorMatrixRowNullPointer : public BaseException
{
    public:
        ErrorMatrixRowNullPointer(void) = delete;
        ErrorMatrixRowNullPointer(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = \
                                  "Unexpected null pointer\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowNullPointer(void) = default;
};

class ErrorMatrixRowAllocation : public BaseException
{
    public:
        ErrorMatrixRowAllocation(void) = delete;
        ErrorMatrixRowAllocation(const char *filename, const size_t line,
                                 const char *function,
                                 const char *message = \
                                 "Unable to allocate memory under row\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowAllocation(void) = default;
};

class ErrorMatrixRowEmptyAllocation : public BaseException
{
    public:
        ErrorMatrixRowEmptyAllocation(void) = delete;
        ErrorMatrixRowEmptyAllocation(const char *filename, const size_t line,
                                 const char *function,
                                 const char *message = \
                                 "Attempt to allocate empty row\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowEmptyAllocation(void) = default;
};

class ErrorMatrixRowEmpty : public BaseException
{
    public:
        ErrorMatrixRowEmpty(void) = delete;
        ErrorMatrixRowEmpty(const char *filename, const size_t line,
                            const char *function,
                            const char *message = \
                            "Row is empty\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowEmpty(void) = default;
};

class ErrorMatrixRowIndexViolation : public BaseException
{
    public:
        ErrorMatrixRowIndexViolation(void) = delete;
        ErrorMatrixRowIndexViolation(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = \
                                     "Attempt ro index out from row range\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowIndexViolation(void) = default;
};

class ErrorMatrixRowIncompatible : public BaseException
{
    public:
        ErrorMatrixRowIncompatible(void) = delete;
        ErrorMatrixRowIncompatible(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Rows have different sizes\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixRowIncompatible(void) = default;
};

#endif

