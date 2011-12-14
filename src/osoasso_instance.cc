#include <string>
#include <sstream>
#include <memory>
#include "../include/osoasso_instance.h"
#include "../include/matrix.h"
#include "../include/matrix_formatter.h"

using namespace osoasso;

static const char message_argument_separator = ':';

osoasso_instance::osoasso_instance(project_manager& manager) : manager_(manager)
{
}

message_output osoasso_instance::handle_message(const std::string& message)
{
    message_output output;
    output.type = message_output_string;

    if (message.find(input_method_id) == 0)
    {
        size_t first_delim = message.find_first_of(message_argument_separator);
        if (first_delim != std::string::npos)
        {
            size_t second_delim = message.find(message_argument_separator, first_delim + 1);
            if (second_delim != std::string::npos)
            {
                std::string action = message.substr(first_delim + 1, second_delim - first_delim - 1);
                std::string user = message.substr(second_delim + 1);
                commit_data data = manager_.input(action, user);
                output.type = message_output_string;

                std::shared_ptr<const matrix<double>> matrix = manager_.get_matrix(data.output);
                matrix_formatter<double> formatter(*matrix);

                std::stringstream output_commit_string;
                output_commit_string << data.name << "#" << data.action << "#" << data.user
                                     << "#" << data.time << "#" << data.output << "#"
                                     << formatter.to_math_jax();
                output.value.commit_string = output_commit_string.str().c_str();
            }
        }
    }
    else if (message.find(get_matrix_method_id) == 0)
    {
        size_t first_delim = message.find_first_of(message_argument_separator);
        if (first_delim != std::string::npos)
        {
            std::string name = message.substr(first_delim + 1);
            std::shared_ptr<const matrix<double>> matrix = manager_.get_matrix(name);
            output.type = message_output_double;
            output.value.matrix_value = (*matrix)(1,1);
        }
    }

    return output;
}
