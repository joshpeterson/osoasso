#include "../test_harness/test.h"
#include "../include/command_parser.h"

using namespace osoasso;

Define(CommandParser)
{
    It("Returns the name of the command")
    {

        command_parser test_parser("foo");
        ASSERT_EQUAL("foo", test_parser.name())

    } Done

    It("Returns the name of the command with inputs in paranthesis")
    {

        command_parser test_parser("bar(1,2)");
        ASSERT_EQUAL("bar", test_parser.name())

    } Done

    It("Returns empty name for empty command")
    {

        command_parser test_parser("");
        ASSERT_EQUAL("", test_parser.name())

    } Done

    It("Returns correct inputs without space after comma")
    {

        command_parser test_parser("bar(1,2)");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("2", actual_inputs[1])

    } Done

    It("Returns empty inputs when command name only is given")
    {

        command_parser test_parser("foo");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(true, actual_inputs.empty())

    } Done

    It("Returns empty inputs when command name is empty")
    {

        command_parser test_parser("");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(true, actual_inputs.empty())

    } Done

    It("Trims spaces from inputs")
    {

        command_parser test_parser("foo( 1 , [2 3] )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("[2 3]", actual_inputs[1])

    } Done

    It("Trims white space from inputs")
    {

        command_parser test_parser("foo( 1\t, \r[2 3]\n )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("[2 3]", actual_inputs[1])

    } Done

    It("Trims white space from command name")
    {

        command_parser test_parser(" \tfoo\r\n(1, [2 3])");
        ASSERT_EQUAL("foo", test_parser.name());

    } Done
}
