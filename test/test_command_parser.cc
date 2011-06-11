#include "../test_harness/test.h"
#include "../include/command_parser.h"

using namespace osoasso;

Define(CommandParser)
{
    It("ReturnsTheNameOfTheCommand")
    {

        command_parser test_parser("foo");
        ASSERT_EQUAL("foo", test_parser.name())

    } Done

    It("ReturnsTheNameofTheCommandWithInputsInParanthesis")
    {

        command_parser test_parser("bar(1,2)");
        ASSERT_EQUAL("bar", test_parser.name())

    } Done

    It("ReturnsEmptyNameForEmptyCommand")
    {

        command_parser test_parser("");
        ASSERT_EQUAL("", test_parser.name())

    } Done

    It("ReturnsCorrectInputsWithoutSpaceAfterComma")
    {

        command_parser test_parser("bar(1,2)");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("2", actual_inputs[1])

    } Done

    It("ReturnsEmptyInputsWhenCommandNameOnlyIsGiven")
    {

        command_parser test_parser("foo");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(true, actual_inputs.empty())

    } Done

    It("ReturnsEmptyInputsWhenCommandNameIsEmpty")
    {

        command_parser test_parser("");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(true, actual_inputs.empty())

    } Done

    It("TrimsSpacesFromInputs")
    {

        command_parser test_parser("foo( 1 , [2 3] )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("[2 3]", actual_inputs[1])

    } Done

    It("TrimsWhiteSpaceFromInputs")
    {

        command_parser test_parser("foo( 1\t, \r[2 3]\n )");
        std::vector<std::string> actual_inputs = test_parser.inputs();
        
        ASSERT_EQUAL(2, actual_inputs.size())
        ASSERT_EQUAL("1", actual_inputs[0])
        ASSERT_EQUAL("[2 3]", actual_inputs[1])

    } Done

    It("TrimsWhiteSpaceFromCommandName")
    {

        command_parser test_parser(" \tfoo\r\n(1, [2 3])");
        ASSERT_EQUAL("foo", test_parser.name());

    } Done
}
