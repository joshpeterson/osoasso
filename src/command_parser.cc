#include "../include/command_parser.h"
#include "../include/trim.h"

using namespace osoasso;

command_parser::command_parser(const std::string& command) : has_tag_(false), command_segments_()
{
    if (command.find("=") != std::string::npos)
        has_tag_ = true;

    std::string delimiters = "=(,)";
    std::string::size_type pos, lastPos = 0;
    while(true)
    {
        pos = command.find_first_of(delimiters, lastPos);
        if(pos == std::string::npos)
        {
            pos = command.length();
            if(pos != lastPos)
            {
                command_segments_.push_back(trim(std::string(command.data()+lastPos, pos-lastPos)));
            }

            break;
        }
        else
        {
            if(pos != lastPos)
            {
                command_segments_.push_back(trim(std::string(command.data()+lastPos, pos-lastPos)));
            }
        }

        lastPos = pos + 1;
    }
}

std::string command_parser::tag() const
{
    if (has_tag_ && !command_segments_.empty())
    {
        return command_segments_[0];
    }

    return std::string();
}

bool command_parser::has_tag() const
{
    return has_tag_;
}

std::string command_parser::name() const
{
    if (!command_segments_.empty())
        return command_segments_[command_name_offset()];

    return std::string();
}

std::vector<std::string> command_parser::inputs() const
{
    if (!command_segments_.empty())
    {
        return std::vector<std::string>(command_segments_.cbegin() + command_name_offset() + 1,
                                        command_segments_.cend());
    }

    return std::vector<std::string>();
}

size_t command_parser::command_name_offset() const
{
    return has_tag_ ? 1 : 0;
}
