#include "../include/command_factory.h"

using namespace osoasso;

command_factory::command_factory(std::initializer_list<std::pair<std::string, std::shared_ptr<command>>> commands) :
    commands_(commands)
{
}

std::shared_ptr<command> command_factory::get(std::string name) const
{
    return commands_.get(name);
}
