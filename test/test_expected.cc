#include <memory>
#include <string>
#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/expected.h"

using namespace osoasso;

Define(Expected)
{
    It("Stores a copy of an instance of type TValue")
    {
        const int value = 42;
        expected<int> expected_int(value);
        AssertEqual(value, expected_int.get_value());
    } Done

    It("Exposes a query to determine if a value exists")
    {
        const int value = 42;
        expected<int> expected_int(value);
        AssertTrue(expected_int.has_value());
    } Done

    It("Exposes a query to determine if a value does not exist")
    {
        expected<int> expected_int = expected<int>::from_exception(std::invalid_argument("Unused"));
        AssertFalse(expected_int.has_value());
    } Done

    It("Throws a runtime_error exception if a value does not exist and get_value is called")
    {
        const std::string expected_message = "Exception message";
        expected<int> expected_int = expected<int>::from_exception(std::invalid_argument(expected_message.c_str()));

        bool exception_occurred = false;
        try
        {
            expected_int.get_value();
        }
        catch (const std::runtime_error& e)
        {
            exception_occurred = true;
            AssertEqual(expected_message, e.what());
        }

        AssertTrue(exception_occurred);
    } Done

    It("Stores the message from the exception")
    {
        const std::string expected_message = "Expected message";
        expected<int> expected_int = expected<int>::from_exception(std::invalid_argument(expected_message));
        AssertEqual(expected_message, expected_int.get_exception_message());
    } Done
}
