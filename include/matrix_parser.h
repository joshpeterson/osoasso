#ifndef __MATRIX_PARSER_H
#define __MATRIX_PARSER_H

#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "matrix.h"
#include "matrix_builder.h"
#include "trim.h"
#include "parse_error.h"

namespace osoasso
{

template <typename ValueType>
class matrix_parser
{
public:
    matrix_parser(std::string value_to_parse) : value_to_parse_(trim(value_to_parse))
    {
    }

    std::shared_ptr<matrix<ValueType>> parse() const
    {
        matrix_builder<ValueType> builder;

        size_t row_start_bracket_position = value_to_parse_.find_first_of('[', 1);
        validate_start_of_first_row(row_start_bracket_position);

        while (row_start_bracket_position != std::string::npos)
        {
            builder.new_row();

            size_t row_end_bracket_position = value_to_parse_.find_first_of(']', row_start_bracket_position);
            if (row_end_bracket_position != std::string::npos)
            {
                validate_end_of_current_row(row_start_bracket_position, row_end_bracket_position);

                std::string row_string_without_brackets = 
                    value_to_parse_.substr(row_start_bracket_position+1,
                                           row_end_bracket_position - (row_start_bracket_position+1));
                parse_row(row_string_without_brackets, builder);
            }
            else
            {
                throw parse_error("Unable to find ] character at the close of the matrix.",
                                  value_to_parse_.size());
            }

            row_start_bracket_position = value_to_parse_.find_first_of('[', row_end_bracket_position+1);
        }

        return builder.done();
    }

private:
    std::string value_to_parse_;

    void parse_row(std::string row_string, matrix_builder<ValueType>& builder) const
    {
        std::istringstream row_stream(row_string);
        std::vector<std::string> row_entries;
        std::copy(std::istream_iterator<std::string>(row_stream),
                  std::istream_iterator<std::string>(),
                  std::back_inserter<std::vector<std::string>>(row_entries));

        for (auto i = row_entries.begin(); i != row_entries.end(); ++i)
        {
            std::istringstream to_value(*i);
            ValueType value;
            to_value >> value;
            builder.add(value);
        }
    }

    void validate_start_of_first_row(size_t position) const
    {
        if (position == std::string::npos)
        {
            throw parse_error("Unable to find [ character to start the first row.", 2);
        }
    }

    void validate_end_of_current_row(size_t row_start_bracket_position, size_t position) const
    {
        size_t previous_row_start_bracket_position = value_to_parse_.find_last_of('[', position);
        if (previous_row_start_bracket_position != row_start_bracket_position)
        {
            throw parse_error("Expected closing ] character for row.", previous_row_start_bracket_position);
        }
    }
};

}

#endif // __MATRIX_PARSER_H
