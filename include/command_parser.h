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
    std::string tag() const;
    bool has_tag() const;
    std::string name() const;
    std::vector<std::string> inputs() const;

private:
    bool has_tag_;
    std::vector<std::string> command_segments_;

    size_t command_name_offset() const;
};

}

#endif // __COMMAND_PARSER_H
