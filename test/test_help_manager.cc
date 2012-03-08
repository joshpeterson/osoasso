#include <string>
#include <sstream>
#include <utility>
#include "../test_harness/test.h"
#include "../include/help_manager.h"
#include "../include/version.h"

using namespace osoasso;

Define(HelpManager)
{
    It("Returns the basic version and help string")
    {
        std::vector<std::pair<std::string, std::string>> command_help;
        help_manager help(command_help);

        std::stringstream help_message;
        help_message << "Osoasso Version " << VERSION << "\n"
                     << "For a list of commands, type this: help commands";
        AssertEqual(help_message.str(), help.get_help_for_action("help"));
    } Done

    It("Returns a list of commands")
    {
        std::vector<std::pair<std::string, std::string>> command_help = { std::make_pair("add", "add help"), std::make_pair("subtract", "subtract help") };
        help_manager help(command_help);
        std::stringstream help_message;
        help_message << "add - add help\n" << "subtract - subtract help\n";
        AssertEqual(help_message.str(), help.get_help_for_action("help commands"));
    } Done
}
