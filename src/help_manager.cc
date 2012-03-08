#include <sstream>
#include "../include/help_manager.h"
#include "../include/version.h"

using namespace osoasso;

help_manager::help_manager(const std::vector<std::string>& command_names) : command_names_(command_names)
{
}

std::string help_manager::get_help_for_action(const std::string& action)
{
    std::stringstream help_message;
    if (action == "help commands")
    {
        for (auto i = command_names_.begin(); i != command_names_.end(); ++i)
        {
            help_message << *i << std::endl;
        }

        return help_message.str();
    }
    else
    {
        help_message << "Osoasso Version " << VERSION << "\n"
                     << "For a list of commands, type this: help commands";
        return help_message.str();
    }
}
