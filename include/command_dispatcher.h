#include <string>
#include "command_factory.h"

namespace osoasso
{

class command_parser;
class command;

class command_dispatcher
{
public:
    command_dispatcher(const command_factory& commands);
    void input(const std::string& input) const;

private:
    const command_factory& commands_;

    void validate_number_of_inputs(const std::string& command_name, const std::vector<std::string>& inputs,
                                   std::shared_ptr<osoasso::command> command) const;
    std::vector<osoasso::matrix<double>> unpack_arguments(const std::vector<std::string>& inputs) const;
};

}
