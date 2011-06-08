#include "../test_harness/test.h"
#include "../include/command_parser.h"

using namespace osoasso;

TEST_FIXTURE_START(CommandParser)

TEST_START(ReturnsTheNameOfTheCommand)

    command_parser test_parser("foo");
    ASSERT_EQUAL("foo", test_parser.name())

TEST_END

TEST_START(ReturnsTheNameofTheCommandWithInputsInParanthesis)

    command_parser test_parser("bar(1,2)");
    ASSERT_EQUAL("bar", test_parser.name())

TEST_END

TEST_START(ReturnsEmptyNameForEmptyCommand)

    command_parser test_parser("");
    ASSERT_EQUAL("", test_parser.name())

TEST_END

TEST_START(ReturnsCorrectInputsWithoutSpaceAfterComma)

    command_parser test_parser("bar(1,2)");
    std::vector<std::string> actual_inputs = test_parser.inputs();
    
    ASSERT_EQUAL(2, actual_inputs.size())
    ASSERT_EQUAL("1", actual_inputs[0])
    ASSERT_EQUAL("2", actual_inputs[1])

TEST_END

TEST_START(ReturnsEmptyInputsWhenCommandNameOnlyIsGiven)

    command_parser test_parser("foo");
    std::vector<std::string> actual_inputs = test_parser.inputs();
    
    ASSERT_EQUAL(true, actual_inputs.empty())

TEST_END

TEST_START(ReturnsEmptyInputsWhenCommandNameIsEmpty)

    command_parser test_parser("");
    std::vector<std::string> actual_inputs = test_parser.inputs();
    
    ASSERT_EQUAL(true, actual_inputs.empty())

TEST_END

TEST_FIXTURE_END
