#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

#include <memory>
#include <initializer_list>

#include "base_exception.h"

class Attribute
{
    public:
        Attribute(const size_t amount);
        Attribute(const size_t amount, std::initializer_list<size_t> indexes);
        Attribute(const Attribute &attr);
        Attribute(Attribute &&attr);

        Attribute &operator = (const Attribute &another);
        Attribute &operator = (Attribute &&another);

        bool operator == (const Attribute &another) const;
        bool operator != (const Attribute &another) const;
        bool operator >  (const Attribute &another) const;
        bool operator <  (const Attribute &another) const;
        bool operator >= (const Attribute &another) const;
        bool operator <= (const Attribute &another) const;

        Attribute  operator &  (const Attribute &another) const;
        Attribute  operator |  (const Attribute &another) const;
        Attribute  operator ^  (const Attribute &another) const;
        Attribute  operator ~  (void)                     const;
        Attribute &operator &= (const Attribute &another);
        Attribute &operator |= (const Attribute &another);
        Attribute &operator ^= (const Attribute &another);

        bool contains(const Attribute &another) const;

        void set(const size_t index) const;
        void reset(const size_t index) const;

        bool get(const size_t index) const;
        bool operator () (const size_t index) const;

    private:
        using AType = unsigned int;
        const int MAX_ASIZE = sizeof(AType) * 8;

        void allocate(const size_t amount);
        void isCompatible(const Attribute &another) const;
        void checkIndex(const size_t index)         const;

        size_t amount;
        size_t real;
        std::unique_ptr<AType[]> arr;
};

class ErrorAttributeIncompatibleException : public BaseException
{
    public:
        ErrorAttributeIncompatibleException(void) = default;
        ErrorAttributeIncompatibleException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Attributes are incompatible")
            : BaseException(filename, line, function, message) {};
        ~ErrorAttributeIncompatibleException(void) = default;
};

class ErrorAttributeIndexViolationException : public BaseException
{
    public:
        ErrorAttributeIndexViolationException(void) = default;
        ErrorAttributeIndexViolationException(const char *filename, const size_t line,
                                            const char *function,
                                            const char *message = "Index out of attribute range")
            : BaseException(filename, line, function, message) {};
        ~ErrorAttributeIndexViolationException(void) = default;
};

class ErrorAttributeAllocationException : public BaseException
{
    public:
        ErrorAttributeAllocationException(void) = default;
        ErrorAttributeAllocationException(const char *filename, const size_t line,
                                          const char *function,
                                          const char *message = "Unable to allocate attribute")
            : BaseException(filename, line, function, message) {};
        ~ErrorAttributeAllocationException(void) = default;
};

class ErrorAttributeALlocationEmptyException : public BaseException
{
    public:
        ErrorAttributeALlocationEmptyException(void) = default;
        ErrorAttributeALlocationEmptyException(const char *filename, const size_t line,
                                          const char *function,
                                          const char *message = "Unable to allocate empty attribute")
            : BaseException(filename, line, function, message) {};
        ~ErrorAttributeALlocationEmptyException(void) = default;
};

#endif

