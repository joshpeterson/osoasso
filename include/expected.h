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
    explicit expected(T value) : _value(value), _has_value(true)
    {
    }

    explicit expected(std::shared_ptr<std::exception> e) : _e(e), _has_value(false)
    {
    }

    bool has_value() const
    {
        return _has_value;
    }

    T get_value() const
    {
        if (!_has_value)
            throw std::logic_error("No value exists to get.");
        return _value;
    }
    
    const std::exception& get_exception() const
    {
        return *_e;
    }

private:
    T _value;
    std::shared_ptr<std::exception> _e;
    bool _has_value;
};

}

#endif //__EXPECTED_H

