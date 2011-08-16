#ifndef __NAMED_OBJECT_H
#define __NAMED_OBJECT_H

#include <string>

namespace osoasso
{

template<typename T>
class named_object
{
public:
    named_object(std::string name, const T& value) : name_(name), value_(value)
    {
    }

    std::string name() const
    {
        return name_;
    }

    T value() const
    {
        return value_;
    }

private:
    const std::string name_;
    const T& value_; 
};

}

#endif // __NAMED_OBJECT_H
