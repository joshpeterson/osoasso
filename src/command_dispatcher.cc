#include <memory>
#include <sstream>
#include <stdexcept>
#include "../include/command_dispatcher.h"
#include "../include/command_parser.h"
#include "../include/matrix_parser.h"
#include "../include/matrix_blobber.h"

using namespace osoasso;

command_dispatcher::command_dispatcher(const command_factory& commands,
                                       object_repository<std::shared_ptr<const matrix<double>>>& matrices)
    : commands_(commands), matrices_(matrices)
{
}

std::string command_dispatcher::input(const std::string& input)
{
    command_parser parser(input);
    std::shared_ptr<command> command = commands_.get(parser.name());

    this->validate_number_of_inputs(parser.name(), parser.inputs(), command);

    std::vector<std::shared_ptr<const matrix<double>>> matrix_inputs = 
                                                                    this->unpack_arguments(parser.inputs());

    this->add_inputs_to_matrix_repository(matrix_inputs);

    auto result = command->call(matrix_inputs[0], matrix_inputs[1]);

    return this->add_to_repository(result);
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

std::vector<std::shared_ptr<const matrix<double>>> command_dispatcher::unpack_arguments(
                                                                const std::vector<std::string>& inputs) const
{
    std::vector<std::shared_ptr<const matrix<double>>> matrix_inputs;
    for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
    {
        matrix_parser<double> parser(*i);
        matrix_inputs.push_back(parser.parse()); 
    }

    return matrix_inputs;
}

void command_dispatcher::add_inputs_to_matrix_repository(
                                            const std::vector<std::shared_ptr<const matrix<double>>>& inputs)
{
    for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
    {
        this->add_to_repository(*i);
    }
}

std::string command_dispatcher::add_to_repository(std::shared_ptr<const matrix<double>> value)
{
    matrix_blobber<double> blobber;
    std::shared_ptr<const blob<double>> blob = blobber.make_blob(value);
    matrices_.add(std::make_pair(blob->name(), value));

    return blob->name();
}
