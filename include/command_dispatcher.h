#ifndef __COMMAND_DISPATCHER_H
#define __COMMAND_DISPATCHER_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "../include/object_repository.h"
#include "../include/command_factory.h"
#include "../include/expected.h"

namespace osoasso
{

class command_parser;
class command;
class tag_repository;

struct command_data
{
    command_data() : command_duration_seconds(0.0)
    {
    }

    command_data(const command_data& other) : output(other.output), inputs(other.inputs),
        tag(other.tag), command_duration_seconds(other.command_duration_seconds)
    {
    }

    command_data(command_data&& other) : output(std::move(other.output)), inputs(std::move(other.inputs)),
        tag(std::move(other.tag)), command_duration_seconds(std::move(other.command_duration_seconds))
    {
    }

    std::string output;
    std::vector<std::string> inputs;
    std::string tag;
    double command_duration_seconds;
};

class command_dispatcher
{
public:
    command_dispatcher(const command_factory& commands,
                       object_repository<std::shared_ptr<const matrix<double>>>& matrices,
                       tag_repository& tags);
    expected<command_data> input(const std::string& input);

private:
    const command_factory& commands_;
    object_repository<std::shared_ptr<const matrix<double>>>& matrices_;
    tag_repository& tags_;

    expected<command_data> validate_number_of_inputs(const std::string& command_name, const std::vector<std::string>& inputs,
                                                     std::shared_ptr<osoasso::command> command, bool allow_optional_parameter) const;
    std::vector<std::shared_ptr<const osoasso::matrix<double>>> unpack_arguments(const std::vector<std::string>& inputs) const;
    std::vector<std::string> add_inputs_to_matrix_repository(const std::vector<std::shared_ptr<const osoasso::matrix<double>>>& inputs);
    std::string add_to_object_repository(std::shared_ptr<const osoasso::matrix<double>> value);

    bool is_number(const std::string& input) const;
};

}

#endif //__COMMAND_DISPATCHER_H
