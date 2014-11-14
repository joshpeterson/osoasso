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

    explicit expected(T&& value) : value_(std::move(value_)) , has_value_(true)
    {
    }

    expected(const expected& rhs): has_value_(rhs.has_value_)
    {
        if (has_value_)
            new(&value_)T(rhs.value_);
        else
            new(&e_) std::exception_ptr(rhs.e_);
        message_ = rhs.message_;
    }

    expected(expected&& rhs) : has_value_(rhs.has_value_)
    {
        if(has_value_)
            new(&value_) T(std::move(rhs.value_));
        else
            new(&e_) std::exception_ptr(std::move(rhs.e_));
        message_ = std::move(rhs.message_);
    }

    ~expected()
    {
        if (has_value_)
            value_.~T();
        else
            e_.~exception_ptr();
    }

    bool has_value() const
    {
        return has_value_;
    }

    T& get_value()
    {
        if (!has_value_)
            std::rethrow_exception(e_);
        return value_;
    }

    const T& get_value() const
    {
        if(!has_value_)
            std::rethrow_exception(e_);
        return value_;
    }

    const char* get_exception_message() const
    {
        return message_.c_str();
    }

    template<class E>
    static expected<T> from_exception(const E& exception)
    {
        if(typeid(exception)!=typeid(E))
            throw std::invalid_argument("slicingdetected");

        expected<T> result;
        result.has_value_ = false; 
        new(&result.e_) std::exception_ptr(std::make_exception_ptr(exception));
        result.message_ = exception.what();

        return result;
    }

private:
    union
    {
        T value_;
        std::exception_ptr e_;
    };
    bool has_value_;
    std::string message_;
    expected() {}
};

}

#endif //__EXPECTED_H

