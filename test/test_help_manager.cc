#include <string>
#include <sstream>
#include "../test_harness/test.h"
#include "../include/help_manager.h"
#include "../include/version.h"

using namespace osoasso;

Define(HelpManager)
{
    It("Returns the basic version and help string")
    {
        std::vector<std::string> command_names;
        help_manager help(command_names);

        std::stringstream help_message;
        help_message << "Osoasso Version: " << VERSION << "\n"
                     << "For a list of commands, type help commands";
        AssertEqual(help_message.str(), help.get_help_for_action("help"));
    } Done

    It("Returns a list of commands")
    {
        std::vector<std::string> command_names = { "add", "subtract" };
        help_manager help(command_names);
        std::stringstream help_message;
        help_message << "add\n" << "subtract\n";
        AssertEqual(help_message.str(), help.get_help_for_action("help commands"));
    } Done
}
