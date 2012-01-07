#ifndef __COMMAND_PARSER_H
#define __COMMAND_PARSER_H

#include <string>
#include <vector>

namespace osoasso
{

class command_parser
{
public:
    command_parser(const std::string& command);
    std::string name() const;
    std::vector<std::string> inputs() const;

private:
    std::vector<std::string> command_segments_;
};

}

#endif // __COMMAND_PARSER_H
