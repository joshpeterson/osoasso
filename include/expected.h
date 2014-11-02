#ifndef __EXPECTED_H
#define __EXPECTED_H

#include <memory>
#include <exception>

namespace osoasso
{

template <typename T>
class expected
{
public:
    explicit expected(T value) : value_(value), has_value_(true)
    {
    }

    explicit expected(std::shared_ptr<std::exception> e) : e_(e), has_value_(false)
    {
    }

    bool has_value() const
    {
        return has_value_;
    }

    T& get_value()
    {
        if (!has_value_)
            throw std::logic_error("No value exists to get.");
        return value_;
    }
    
    std::shared_ptr<std::exception> get_exception()
    {
        return e_;
    }

private:
    T value_;
    std::shared_ptr<std::exception> e_;
    bool has_value_;
};

}

#endif //__EXPECTED_H

