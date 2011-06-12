#include "../test_harness/test.h"
#include "../include/command_parser.h"

using namespace osoasso;

Define(CommandParser)
{
    It("Returns the name of the command")
    {
        command_parser test_parser("foo");
        AssertEqual<std::string>("foo", test_parser.name());
    } Done

    It("Returns the name of the command with inputs in paranthesis")
    {
        command_parser test_parser("bar(1,2)");
        AssertEqual<std::string>("bar", test_parser.name());
    } Done

    It("Returns empty name for empty command")
    {
        command_parser test_parser("");
        AssertEqual<std::string>("", test_parser.name());
    } Done

    It("Returns correct inputs without space after comma")
    {
        command_parser test_parser("bar(1,2)");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertEqual<size_t>(2, actual_inputs.size());
        AssertEqual<std::string>("1", actual_inputs[0]);
        AssertEqual<std::string>("2", actual_inputs[1]);
    } Done

    It("Returns empty inputs when command name only is given")
    {
        command_parser test_parser("foo");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertTrue(actual_inputs.empty());
    } Done

    It("Returns empty inputs when command name is empty")
    {
        command_parser test_parser("");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertTrue(actual_inputs.empty());
    } Done

    It("Trims spaces from inputs")
    {
        command_parser test_parser("foo( 1 , [2 3] )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertEqual<size_t>(2, actual_inputs.size());
        AssertEqual<std::string>("1", actual_inputs[0]);
        AssertEqual<std::string>("[2 3]", actual_inputs[1]);
    } Done

    It("Trims white space from inputs")
    {
        command_parser test_parser("foo( 1\t, \r[2 3]\n )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertEqual<size_t>(2, actual_inputs.size());
        AssertEqual<std::string>("1", actual_inputs[0]);
        AssertEqual<std::string>("[2 3]", actual_inputs[1]);
    } Done

    It("Trims white space from command name")
    {
        command_parser test_parser(" \tfoo\r\n(1, [2 3])");
        AssertEqual<std::string>("foo", test_parser.name());
    } Done
}
