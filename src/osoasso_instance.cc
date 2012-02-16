#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "../include/osoasso_instance.h"
#include "../include/matrix.h"
#include "../include/matrix_formatter.h"

using namespace osoasso;

static const char message_argument_separator = ':';

osoasso_instance::osoasso_instance(project_manager& manager) : manager_(manager)
{
}

std::string osoasso_instance::handle_message(const std::string& message)
{
    std::stringstream output_commit_string;

    size_t first_delim = message.find_first_of(message_argument_separator);
    if (first_delim != std::string::npos)
    {
        size_t second_delim = message.find(message_argument_separator, first_delim + 1);
        if (second_delim != std::string::npos)
        {
            std::string action = message.substr(first_delim + 1, second_delim - first_delim - 1);
            std::string user = message.substr(second_delim + 1);
            try
            {
                commit_data data = manager_.input(action, user);

                output_commit_string << data.name << "#" << data.action << "#" << data.user
                                     << "#" << data.time << "#" << data.command_time << "#"
                                     << data.output;

                if (data.tag.size() == 0)
                {
                    std::shared_ptr<const matrix<double>> matrix = manager_.get_matrix(data.output);
                    matrix_formatter<double> formatter(*matrix);
                    output_commit_string << "#" << formatter.to_html_table();
                }
            }
            catch (const std::exception& e)
            {
                output_commit_string << "error#" << action << "#" << e.what();
            }
        }
    }

    return output_commit_string.str();
}
