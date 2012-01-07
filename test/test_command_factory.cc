#include <utility>
#include <memory>
#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/command.h"
#include "../include/command_factory.h"

using namespace osoasso;

class mock_command : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const
    {
        auto test = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));
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
        AssertEqual(15, actual_command->number_of_arguments());
    } Done
}

