#include "base_exception.h"

BaseException::BaseException(const char *filename, const size_t line,
                             const char *function, const char *message)
{
    this->message = std::string(message) 
                    + "\n\t\tAt line " + std::to_string(line)
                    + " in file \"" + std::string(filename) + "\"\n"
                    + "\t\tIn function \"" + std::string(function) + "\"\n";
}

const char *BaseException::what(void) const noexcept
{
    return (this->message).c_str();
}

