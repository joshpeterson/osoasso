#include <memory>
#include <sstream>
#include <stdexcept>
#include "../include/command_dispatcher.h"
#include "../include/command_parser.h"
#include "../include/matrix_parser.h"
#include "../include/matrix.h"

using namespace osoasso;

command_dispatcher::command_dispatcher(const command_factory& commands) : commands_(commands)
{
}

void command_dispatcher::input(const std::string& input) const
{
    command_parser parser(input);
    std::shared_ptr<command> command = commands_.get(parser.name());

    this->validate_number_of_inputs(parser.name(), parser.inputs(), command);

    std::vector<std::shared_ptr<matrix<double>>> matrix_inputs = this->unpack_arguments(parser.inputs());

    command->call(matrix_inputs[0], matrix_inputs[1]);
}

void command_dispatcher::validate_number_of_inputs(const std::string& command_name,
                                                   const std::vector<std::string>& inputs,
                                                   std::shared_ptr<command> command) const
{
    int number_of_arguments_provided = static_cast<int>(inputs.size());
    int number_of_arguments_expected = command->number_of_arguments();
    if (number_of_arguments_provided != number_of_arguments_expected)
    {
        std::stringstream message;
        message << "Command " << command_name << " expected " << number_of_arguments_expected
                << (number_of_arguments_expected == 1 ? " argument" : " arguments")
                << " but" << number_of_arguments_provided
                << (number_of_arguments_provided == 1 ? " argument" : " arugments")
                << " were provided:" << std::endl;
        for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
        {
            message << *i << std::endl;
        }

        throw std::runtime_error(message.str());
    }
}

std::vector<std::shared_ptr<matrix<double>>> command_dispatcher::unpack_arguments(
                                                                const std::vector<std::string>& inputs) const
{
    std::vector<std::shared_ptr<matrix<double>>> matrix_inputs;
    for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
    {
        matrix_parser<double> parser(*i);
        matrix_inputs.push_back(parser.parse()); 
    }

    return matrix_inputs;
}
