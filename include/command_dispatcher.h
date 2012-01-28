#ifndef __COMMAND_DISPATCHER_H
#define __COMMAND_DISPATCHER_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "../include/object_repository.h"
#include "../include/command_factory.h"

namespace osoasso
{

class command_parser;
class command;
class tag_repository;

struct command_data
{
    command_data()
    {
    }

    command_data(command_data&& other) : output(std::move(other.output)), inputs(std::move(other.inputs)),
        tag(std::move(other.tag)), command_time(std::move(other.command_time))
    {
    }

    std::string output;
    std::vector<std::string> inputs;
    std::string tag;
    double command_time;
};

class command_dispatcher
{
public:
    command_dispatcher(const command_factory& commands,
                       object_repository<std::shared_ptr<const matrix<double>>>& matrices,
                       tag_repository& tags);
    command_data input(const std::string& input);

private:
    const command_factory& commands_;
    object_repository<std::shared_ptr<const matrix<double>>>& matrices_;
    tag_repository& tags_;

    void validate_number_of_inputs(const std::string& command_name, const std::vector<std::string>& inputs,
                                   std::shared_ptr<osoasso::command> command) const;
    std::vector<std::shared_ptr<const osoasso::matrix<double>>> unpack_arguments(
                                                            const std::vector<std::string>& inputs) const;
    std::vector<std::string> add_inputs_to_matrix_repository(
                                const std::vector<std::shared_ptr<const osoasso::matrix<double>>>& inputs);
    std::string add_to_object_repository(std::shared_ptr<const osoasso::matrix<double>> value);
};

}

#endif //__COMMAND_DISPATCHER_H
