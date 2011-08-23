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

private:
    mutable bool command_called_;
};

Define(CommandDispatcher)
{
    It ("Accepts an input string and calls the correct command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();
        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        command_dispatcher dispatcher(commands);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertTrue(test_command->command_called());
    } Done
}
