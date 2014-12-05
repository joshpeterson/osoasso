#include <sstream>
#include "../include/help_manager.h"
#include "../include/version.h"

using namespace osoasso;

help_manager::help_manager(const std::vector<std::pair<std::string, std::string>>& command_help) : command_help_(command_help)
{
}

std::string help_manager::get_help_for_action(const std::string& action)
{
    std::stringstream help_message;
    if (action == "help commands")
    {
        for (auto i = command_help_.begin(); i != command_help_.end(); ++i)
        {
            help_message << i->first << " - " << i->second << std::endl;
        }

        return help_message.str();
    }
    else
    {
        help_message << "Osoasso Version " << VERSION << " (" << TARGET << ")\n"
                     << "For a list of commands, type this: help commands";
        return help_message.str();
    }
}
