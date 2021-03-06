#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "../include/osoasso_instance.h"
#include "../include/matrix.h"
#include "../include/matrix_formatter.h"

using namespace osoasso;

static const char message_argument_separator = ':';

osoasso_instance::osoasso_instance(project_manager& manager) : manager_(manager), help_(manager_.get_command_help())
{
}

std::string osoasso_instance::handle_message(const std::string& message)
{
    std::stringstream output;

    size_t first_delim = message.find_first_of(message_argument_separator);
    if (first_delim != std::string::npos)
    {
        size_t second_delim = message.find(message_argument_separator, first_delim + 1);
        if (second_delim != std::string::npos)
        {
            std::string action = message.substr(first_delim + 1, second_delim - first_delim - 1);
            std::string user = message.substr(second_delim + 1);

            if (action.substr(0, 4) == "help")
            {
                std::string help_message = help_.get_help_for_action(action);
                output << "text#" << action << "#" << help_message;
            }
            else
            {
                auto expected_data = manager_.input(action, user);
                if (expected_data.has_value())
                {
                    auto data = expected_data.get_value();
                    output << data.name << "#" << data.action << "#" << data.user
                                         << "#" << data.time << "#" << data.command_duration_seconds << "#"
                                         << data.output;

                    if (data.tag.size() == 0)
                    {
                        std::shared_ptr<const matrix<double>> matrix = manager_.get_matrix(data.output);
                        matrix_formatter<double> formatter(*matrix);
                        output << "#" << formatter.to_html_table();
                    }
                }
                else
                {
                    output << "error#" << action << "#" << expected_data.get_exception_message();
                }
            }
        }
    }

    return output.str();
}
