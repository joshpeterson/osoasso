#include <utility>
#include <memory>
#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/command.h"
#include "../include/command_factory.h"

using namespace osoasso;

class mock_command : public command
{
public:
    matrix<double> call(const matrix<double>& left, const matrix<double>& right) const
    {
        matrix<double> test = {{1}, {1}};
        return test;
    }

    int number_of_arguments() const
    {
        return 15;
    }
};

Define(CommandFactory)
{
    It("Can be created with an initialization list")
    {
        command_factory commands = { std::make_pair("mock", std::shared_ptr<command>(new mock_command)) };
    } Done

    It("Can find a command by name")
    {
        command_factory commands = { std::make_pair("mock", std::shared_ptr<command>(new mock_command)) };

        std::shared_ptr<command> actual_command = commands.get("mock");
    } Done
}

