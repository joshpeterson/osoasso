#ifndef __STRING_SPLITTER_H
#define __STRING_SPLITTER_H

#include <string>

namespace osoasso
{

class string_splitter
{
public:
    string_splitter(const std::string& input, size_t part_length) : number_of_parts_(0), parts_()
    {
        size_t position = 0;
        while (position < input.size())
        {
            parts_.push_back(input.substr(position, part_length));
            number_of_parts_++;
            position += part_length;
        }
    }

    int number_of_parts() const
    {
        return number_of_parts_;
    }

    std::string part(int part_index) const
    {
        return parts_[part_index];
    }

private:
    int number_of_parts_;
    std::vector<std::string> parts_;
};

}

#endif // __STRING_SPLITTER_H
