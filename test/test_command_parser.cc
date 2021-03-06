#include "../test_harness/test.h"
#include "../include/command_parser.h"

using namespace osoasso;

Define(CommandParser)
{
    It("Returns the name of the command")
    {
        command_parser test_parser("foo");
        AssertEqual("foo", test_parser.name());
    } Done

    It("Returns the name of the command with inputs in paranthesis")
    {
        command_parser test_parser("bar(1,2)");
        AssertEqual("bar", test_parser.name());
    } Done

    It("Returns empty name for empty command")
    {
        command_parser test_parser("");
        AssertEqual("", test_parser.name());
    } Done

    It("Returns correct inputs without space after comma")
    {
        command_parser test_parser("bar(1,2)");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertEqual<size_t>(2, actual_inputs.size());
        AssertEqual("1", actual_inputs[0]);
        AssertEqual("2", actual_inputs[1]);
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
        AssertEqual("1", actual_inputs[0]);
        AssertEqual("[2 3]", actual_inputs[1]);
    } Done

    It("Trims white space from inputs")
    {
        command_parser test_parser("foo( 1\t, \r[2 3]\n )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        AssertEqual<size_t>(2, actual_inputs.size());
        AssertEqual("1", actual_inputs[0]);
        AssertEqual("[2 3]", actual_inputs[1]);
    } Done

    It("Trims white space from command name")
    {
        command_parser test_parser(" \tfoo\r\n(1, [2 3])");
        AssertEqual("foo", test_parser.name());
    } Done

    It("Gets the tag name from an assignment")
    {
        command_parser test_parser("tag=foo(1, [2 3])");
        AssertEqual("tag", test_parser.tag());
    } Done

    It("Trims white space from tag")
    {
        command_parser test_parser(" tag =  \tfoo(1, [2 3])");
        AssertEqual("tag", test_parser.tag());
    } Done

    It("Can report when a tag does not exist in the input.")
    {
        command_parser test_parser("foo(1, [2 3])");
        AssertFalse(test_parser.has_tag());
    } Done

    It("Can report when a tag exists in the input.")
    {
        command_parser test_parser("tag = foo(1, [2 3])");
        AssertTrue(test_parser.has_tag());
    } Done
}
