#include <string>

class mock_named_object
{
public:
    mock_named_object(std::string name) : name_(name)
    {
    }

    std::string name() const
    {
        return name_;
    }

private:
    std::string name_;
};
