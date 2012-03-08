#include <utility>
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
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

    It("Returns a list of command names")
    {
        command_factory commands = { std::make_pair("mock", std::shared_ptr<command>(new mock_command)) };
        std::vector<std::string> names = commands.get_names();
        AssertEqual(std::string("mock"), names[0]);
    } Done

    It("Returns a list of command names sorted alphabetically")
    {
        command_factory commands = { std::make_pair("mock", std::shared_ptr<command>(new mock_command)),
                                     std::make_pair("add", std::shared_ptr<command>(new mock_command)),
                                     std::make_pair("subtract", std::shared_ptr<command>(new mock_command)) };

        std::vector<std::string> names = commands.get_names();

        AssertEqual(std::string("add"), names[0]);
        AssertEqual(std::string("mock"), names[1]);
        AssertEqual(std::string("subtract"), names[2]);
    } Done
}

