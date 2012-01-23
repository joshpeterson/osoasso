#include <memory>
#include <sstream>
#include <stdexcept>
#include "../include/command_dispatcher.h"
#include "../include/command_parser.h"
#include "../include/matrix_parser.h"
#include "../include/matrix_blobber.h"
#include "../include/tag_repository.h"

using namespace osoasso;

command_dispatcher::command_dispatcher(const command_factory& commands,
                                       object_repository<std::shared_ptr<const matrix<double>>>& matrices,
                                       tag_repository& tags)
    : commands_(commands), matrices_(matrices), tags_(tags)
{
}

std::pair<std::string, std::vector<std::string>> command_dispatcher::input(const std::string& input)
{
    command_parser parser(input);
    std::shared_ptr<command> command = commands_.get(parser.name());

    this->validate_number_of_inputs(parser.name(), parser.inputs(), command);

    std::vector<std::shared_ptr<const matrix<double>>> matrix_inputs = 
                                                                    this->unpack_arguments(parser.inputs());

    std::vector<std::string> input_names = this->add_inputs_to_matrix_repository(matrix_inputs);

    auto result = command->call(matrix_inputs[0], matrix_inputs[1]);

    std::string result_name = this->add_to_object_repository(result);

    if (parser.has_tag())
        tags_.add(parser.tag(), result_name);

    return std::make_pair(result_name, input_names);
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
                << " but " << number_of_arguments_provided
                << (number_of_arguments_provided == 1 ? " argument" : " arugments")
                << (number_of_arguments_provided == 1 ? " was" : " were")
                << " provided: ";
        for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
        {
            message << *i;
            if (i != inputs.cend() - 1)
                message << ", ";
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
        if (i->length() != 0 && (*i)[0] != '[')
        {
            std::string matrix_name = *i;
            if (tags_.contains(*i))
            {
                matrix_name = tags_.get(*i);
            }

            matrix_inputs.push_back(matrices_.get(matrix_name));
        }
        else
        {
            matrix_parser<double> parser(*i);
            matrix_inputs.push_back(parser.parse()); 
        }
    }

    return matrix_inputs;
}

std::vector<std::string> command_dispatcher::add_inputs_to_matrix_repository(
                                            const std::vector<std::shared_ptr<const matrix<double>>>& inputs)
{
    std::vector<std::string> input_names;
    for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
    {
        input_names.push_back(this->add_to_object_repository(*i));
    }

    return input_names;
}

std::string command_dispatcher::add_to_object_repository(std::shared_ptr<const matrix<double>> value)
{
    matrix_blobber<double> blobber;
    std::shared_ptr<const blob<double>> blob = blobber.make_blob(value);
    matrices_.add(std::make_pair(blob->name(), value));

    return blob->name();
}
