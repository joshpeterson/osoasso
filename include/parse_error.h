#ifndef __PARSE_ERROR_H
#define __PARSE_ERROR_H

#include <string>
#include <stdexcept>

namespace osoasso
{

class parse_error : public std::exception
{
public:
    parse_error(std::string message, size_t position) : message_(message), position_(position)
    {
    }

    virtual ~parse_error() throw()
    {
    }

    virtual const char* what() const throw()
    {
        return message_.c_str();
    }

    size_t position() const
    {
        return position_;
    }

private:
    std::string message_;
    size_t position_;
};

}

#endif // __PARSE_ERROR_H
