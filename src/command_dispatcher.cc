#include <memory>
#include <sstream>
#include <stdexcept>
#include "../include/command_with_one_argument.h"
#include "../include/command_with_two_arguments.h"
#include "../include/command_dispatcher.h"
#include "../include/command_parser.h"
#include "../include/matrix_parser.h"
#include "../include/matrix_blobber.h"
#include "../include/tag_repository.h"
#include "../include/timer.h"

#include <iostream>

using namespace osoasso;

command_dispatcher::command_dispatcher(const command_factory& commands,
                                       object_repository<std::shared_ptr<const matrix<double>>>& matrices,
                                       tag_repository& tags)
    : commands_(commands), matrices_(matrices), tags_(tags)
{
}

expected<command_data> command_dispatcher::input(const std::string& input)
{
    command_parser parser(input);
    std::shared_ptr<command> command = commands_.get(parser.name());

    std::vector<std::shared_ptr<const matrix<double>>> matrix_inputs = this->unpack_arguments(parser.inputs());

    bool has_optional_parameter = false;
    if (matrix_inputs.size() == static_cast<size_t>(command->number_of_arguments() + 1) &&
        matrix_inputs.back()->rows() == 1 && matrix_inputs.back()->columns() == 1)
        has_optional_parameter = true;

    auto expected_command_data = this->validate_number_of_inputs(parser.name(), parser.inputs(), command, has_optional_parameter);
    if (!expected_command_data.has_value())
        return expected_command_data;

    int number_of_threads = 1;
    if (has_optional_parameter)
    {
        number_of_threads = (*matrix_inputs.back())(1,1);
        matrix_inputs.pop_back();
    }

    std::vector<std::string> input_names = this->add_inputs_to_matrix_repository(matrix_inputs);

    command_data command_result;

    std::shared_ptr<const matrix<double>> result;

    timer command_timer;
    if (command->number_of_arguments() == 2)
    {
        command_with_two_arguments* command_two = (command_with_two_arguments*)command.get();
        auto expected_result = command_two->call(matrix_inputs[0], matrix_inputs[1], number_of_threads);
        if (expected_result.has_value())
            result = expected_result.get_value();
    }
    else
    {
        command_with_one_argument* command_one = (command_with_one_argument*)command.get();
        auto expected_result = command_one->call(matrix_inputs[0], number_of_threads);
        if (expected_result.has_value())
            result = expected_result.get_value();
    }

    command_result.command_duration_seconds = command_timer.elapsed();

    std::string result_name = this->add_to_object_repository(result);

    if (parser.has_tag())
    {
        tags_.add(parser.tag(), result_name);
        command_result.tag = parser.tag();
    }

    command_result.output = result_name;
    command_result.inputs = input_names;

    return expected<command_data>(command_result);
}

expected<command_data> command_dispatcher::validate_number_of_inputs(const std::string& command_name, const std::vector<std::string>& inputs,
                                                   std::shared_ptr<command> command, bool allow_optional_parameter) const
{
    int arguments_provided = static_cast<int>(inputs.size());
    int arguments_expected = command->number_of_arguments();
    if ((allow_optional_parameter && (arguments_provided < arguments_expected || arguments_provided > arguments_expected + 1)) ||
        (!allow_optional_parameter && arguments_provided != arguments_expected))
    {
        std::stringstream message;
        message << "Command " << command_name << " expected " << arguments_expected
                << (arguments_expected == 1 ? " argument" : " arguments")
                << " but " << arguments_provided
                << (arguments_provided == 1 ? " argument" : " arguments")
                << (arguments_provided == 1 ? " was" : " were")
                << " provided: ";
        for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
        {
            message << *i;
            if (i != inputs.cend() - 1)
                message << ", ";
        }

        return expected<command_data>::from_exception(std::runtime_error(message.str()));
    }

    return expected<command_data>(command_data());
}

std::vector<std::shared_ptr<const matrix<double>>> command_dispatcher::unpack_arguments(const std::vector<std::string>& inputs) const
{
    std::vector<std::shared_ptr<const matrix<double>>> matrix_inputs;
    for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
    {
        if (i->length() != 0 && (*i)[0] != '[')
        {
            if (tags_.contains(*i))
            {
                // First look for a tag name
                matrix_inputs.push_back(matrices_.get(tags_.get(*i).get_value()));
            }
            else if (is_number(*i))
            {
                // Then see if the input is a single number
                std::istringstream to_value(*i);
                double value;
                to_value >> value;
                matrix_inputs.push_back(std::shared_ptr<const matrix<double>>(new matrix<double>({{value}})));
            }
            else
            {
                // Finally the input may be a matrix SHA1 name
                matrix_inputs.push_back(matrices_.get(*i));
            }
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

bool command_dispatcher::is_number(const std::string& input) const
{
    for (auto i = input.begin(); i != input.end(); ++i)
    {
        if (!isdigit(*i) && *i != '.')
        {
            return false;
        }
    }

    return true;
}
