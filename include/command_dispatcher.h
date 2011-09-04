#include <string>
#include <memory>
#include "../include/object_repository.h"
#include "../include/command_factory.h"

namespace osoasso
{

class command_parser;
class command;

class command_dispatcher
{
public:
    command_dispatcher(const command_factory& commands,
                       object_repository<std::shared_ptr<const matrix<double>>>& matrices);
    void input(const std::string& input);

private:
    const command_factory& commands_;
    object_repository<std::shared_ptr<const matrix<double>>>& matrices_;

    void validate_number_of_inputs(const std::string& command_name, const std::vector<std::string>& inputs,
                                   std::shared_ptr<osoasso::command> command) const;
    std::vector<std::shared_ptr<const osoasso::matrix<double>>> unpack_arguments(
                                                            const std::vector<std::string>& inputs) const;
    void add_inputs_to_matrix_repository(
                                const std::vector<std::shared_ptr<const osoasso::matrix<double>>>& inputs);
};

}
