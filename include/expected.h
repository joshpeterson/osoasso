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
    explicit expected(const T& value) : value_(value), has_value_(true)
    {
    }

    expected(const expected& rhs): value_(rhs.value_), has_value_(rhs.has_value_), message_(rhs.message_)
    {
    }

    bool has_value() const
    {
        return has_value_;
    }

    T& get_value()
    {
        if (!has_value_)
            throw std::runtime_error(message_);
        return value_;
    }

    const T& get_value() const
    {
        if(!has_value_)
            throw std::runtime_error(message_);
        return value_;
    }

    const char* get_exception_message() const
    {
        return message_.c_str();
    }

    template<class E>
    static expected<T> from_exception(const E& exception)
    {
        return from_string(exception.what());
    }

    static expected<T> from_string(const char* message)
    {
        expected<T> result;
        result.has_value_ = false; 
        result.message_ = message;

        return result;
    }

private:
    T value_;
    bool has_value_;
    std::string message_;
    expected() {}
};

}

#endif //__EXPECTED_H

