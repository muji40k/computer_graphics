#ifndef _BASE_EXCEPTION_H_
#define _BASE_EXCEPTION_H_

#include <string>
#include <exception>

#define DEFAULT_EXCEPTION "Exception occured"

#define CALL_EX(exception) exception(__FILE__, __LINE__, __FUNCTION__);

class BaseException : public std::exception
{
    public:
        BaseException(void) = default;
        BaseException(const char *filename, const size_t line,
                      const char *function,
                      const char *message = DEFAULT_EXCEPTION);
        ~BaseException(void) = default;

        virtual const char *what(void) const noexcept override;

    protected:
        std::string message = DEFAULT_EXCEPTION;
};

#endif

