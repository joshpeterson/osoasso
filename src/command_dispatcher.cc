#include <memory>
#include "../include/command_dispatcher.h"
#include "../include/command_parser.h"

using namespace osoasso;

command_dispatcher::command_dispatcher(const command_factory& commands) : commands_(commands)
{
}

void command_dispatcher::input(const std::string& input) const
{
    command_parser parser(input);
    std::shared_ptr<command> command = commands_.get(parser.name());
    matrix<double> test = {{1}, {1}};
    command->call(test, test);
}
