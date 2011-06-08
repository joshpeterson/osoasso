#include "../include/command_parser.h"

using namespace osoasso;

command_parser::command_parser(std::string command) : command_segments_()
{
    std::string delimiters = "(,)";
    std::string::size_type pos, lastPos = 0;
    while(true)
    {
        pos = command.find_first_of(delimiters, lastPos);
        if(pos == std::string::npos)
        {
            pos = command.length();
            if(pos != lastPos)
            {
                command_segments_.push_back(std::string(command.data()+lastPos, pos-lastPos));
            }

            break;
        }
        else
        {
            if(pos != lastPos)
            {
                command_segments_.push_back(std::string(command.data()+lastPos, pos-lastPos));
            }
        }

        lastPos = pos + 1;
    }
}

std::string command_parser::name() const
{
    if (!command_segments_.empty())
    {
        return command_segments_[0];
    }

    return std::string();
}

std::vector<std::string> command_parser::inputs() const
{
    if (!command_segments_.empty())
    {
        return std::vector<std::string>(command_segments_.cbegin() + 1, command_segments_.cend());
    }

    return std::vector<std::string>();
}
