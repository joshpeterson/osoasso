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

namespace osoasso
{

template <typename ValueType>
class matrix_parser
{
public:
    matrix_parser(std::string value_to_parse) : value_to_parse_(value_to_parse)
    {
    }

    std::shared_ptr<matrix<ValueType>> parse() const
    {
        matrix_builder<ValueType> builder;

        std::string trimmed_value = trim(value_to_parse_);

        size_t row_start_bracket_position = trimmed_value.find_first_of('[', 1);
        while (row_start_bracket_position != std::string::npos)
        {
            builder.new_row();
            size_t row_end_bracket_position = trimmed_value.find_first_of(']', row_start_bracket_position);
            if (row_end_bracket_position != std::string::npos)
            {
                std::string row_string_without_brackets = 
                    trimmed_value.substr(row_start_bracket_position+1,
                                           row_end_bracket_position - (row_start_bracket_position+1));
                parse_row(row_string_without_brackets, builder);
            }

            row_start_bracket_position = trimmed_value.find_first_of('[', row_end_bracket_position+1);
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
};

}

#endif // __MATRIX_PARSER_H
