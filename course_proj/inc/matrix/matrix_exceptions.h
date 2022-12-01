#ifndef _MATRIX_EXCEPTIONS_H_
#define _MATRIX_EXCEPTIONS_H_

#include "base_exception.h"

class ErrorMatrixNullPointer : public BaseException
{
    public:
        ErrorMatrixNullPointer(void) = delete;
        ErrorMatrixNullPointer(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = \
                                  "Unexpected null pointer\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixNullPointer(void) = default;
};

class ErrorMatrixOddInitialization : public BaseException
{
    public:
        ErrorMatrixOddInitialization(void) = delete;
        ErrorMatrixOddInitialization(const char *filename, const size_t line,
                                  const char *function,
                                  const char *message = \
                                  "Sizes of each row must be the same\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixOddInitialization(void) = default;
};

class ErrorMatrixAllocation : public BaseException
{
    public:
        ErrorMatrixAllocation(void) = delete;
        ErrorMatrixAllocation(const char *filename, const size_t line,
                                 const char *function,
                                 const char *message = \
                                 "Unable to allocate memory under matrix\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixAllocation(void) = default;
};

class ErrorMatrixEmptyAllocation : public BaseException
{
    public:
        ErrorMatrixEmptyAllocation(void) = delete;
        ErrorMatrixEmptyAllocation(const char *filename, const size_t line,
                                 const char *function,
                                 const char *message = \
                                 "Attempt to allocate empty matrix\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixEmptyAllocation(void) = default;
};

class ErrorMatrixEmpty : public BaseException
{
    public:
        ErrorMatrixEmpty(void) = delete;
        ErrorMatrixEmpty(const char *filename, const size_t line,
                            const char *function,
                            const char *message = \
                            "Matrix is empty\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixEmpty(void) = default;
};

class ErrorMatrixIndexViolation : public BaseException
{
    public:
        ErrorMatrixIndexViolation(void) = delete;
        ErrorMatrixIndexViolation(const char *filename, const size_t line,
                                     const char *function,
                                     const char *message = \
                                     "Attempt ro index out from matrix range\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixIndexViolation(void) = default;
};

class ErrorMatrixIncompatible : public BaseException
{
    public:
        ErrorMatrixIncompatible(void) = delete;
        ErrorMatrixIncompatible(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Matrixes have different sizes\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixIncompatible(void) = default;
};

class ErrorMatrixInsertionIncompatible : public BaseException
{
    public:
        ErrorMatrixInsertionIncompatible(void) = delete;
        ErrorMatrixInsertionIncompatible(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Inserting row has different size\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixInsertionIncompatible(void) = default;
};

class ErrorMatrixNonSquare : public BaseException
{
    public:
        ErrorMatrixNonSquare(void) = delete;
        ErrorMatrixNonSquare(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Non square matrix\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixNonSquare(void) = default;
};

class ErrorMatrixNoInverted : public BaseException
{
    public:
        ErrorMatrixNoInverted(void) = delete;
        ErrorMatrixNoInverted(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Matrix doesn't have inversed\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixNoInverted(void) = default;
};

class ErrorMatrixNoSolution : public BaseException
{
    public:
        ErrorMatrixNoSolution(void) = delete;
        ErrorMatrixNoSolution(const char *filename, const size_t line,
                                   const char *function,
                                   const char *message = \
                                   "Linera system has no solution\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixNoSolution(void) = default;
};

class ErrorMatrixAllocationSolution : public BaseException
{
    public:
        ErrorMatrixAllocationSolution(void) = delete;
        ErrorMatrixAllocationSolution(const char *filename, const size_t line,
                                 const char *function,
                                 const char *message = \
                                 "Unable to allocate memory under matrix\n")\
        : BaseException(filename, line, function, message) {};
        ~ErrorMatrixAllocationSolution(void) = default;
};

#endif

