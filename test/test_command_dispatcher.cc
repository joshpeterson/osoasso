#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/command_factory.h"
#include "../include/command_dispatcher.h"

using namespace osoasso;

class mock_dispatcher_command : public command
{
public:
    mock_dispatcher_command() : command_called_(false)
    {
    }

    matrix<double> call(const matrix<double>& left, const matrix<double>& right) const
    {
        command_called_ = true;
        left_ = left;
        right_ = right;
        matrix<double> test = {{1}, {1}};
        return test;
    }

    int number_of_arguments() const
    {
        return 2;
    }

    bool command_called() const
    {
        return command_called_;
    }

    matrix<double> left_argument() const
    {
        return left_;
    }

    matrix<double> right_argument() const
    {
        return right_;
    }


private:
    mutable bool command_called_;
    mutable matrix<double> left_;
    mutable matrix<double> right_;
};

Define(CommandDispatcher)
{
    It("Accepts an input string and calls the correct command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();
        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        command_dispatcher dispatcher(commands);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertTrue(test_command->command_called());
    } Done

    It("Throws an exception when it sees the wrong number of arguments")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();
        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        command_dispatcher dispatcher(commands);

        bool exception_thrown = false;
        try
        {
            dispatcher.input("foo([[1 2]], [[3 5]], [[2 6]])");
        }
        catch (const std::runtime_error&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Passes the correct arguments to the command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();
        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        command_dispatcher dispatcher(commands);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        matrix<double> expected_left = {{ 1, 2 }};
        matrix<double> expected_right = {{ 3, 5 }};

        AssertElementsEqual(expected_left, test_command->left_argument());
        AssertElementsEqual(expected_right, test_command->right_argument());
    } Done
}
