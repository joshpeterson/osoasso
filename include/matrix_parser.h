#ifndef __MATRIX_PARSER_H
#define __MATRIX_PARSER_H

#include <string>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "matrix.h"
#include "matrix_builder.h"

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

        bool first_row = true;
        size_t this_row_start_bracket_position = value_to_parse_.find_first_of('[', 1);
        while (this_row_start_bracket_position != std::string::npos)
        {
            if (!first_row)
            {
                builder.new_row();
            }
            else
            {
                first_row = false;
            }

            size_t this_row_end_bracket_position = value_to_parse_.find_first_of(']', this_row_start_bracket_position);
            if (this_row_end_bracket_position != std::string::npos)
            {
                std::istringstream stream(value_to_parse_.substr(this_row_start_bracket_position+1, this_row_end_bracket_position - (this_row_start_bracket_position+1)));
                std::vector<std::string> tokens;
                std::copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(tokens));
                for (auto i = tokens.begin(); i != tokens.end(); ++i)
                {
                    std::istringstream to_double(*i);
                    double value;
                    to_double >> value;
                    builder.add(value);
                }
            }

            this_row_start_bracket_position = value_to_parse_.find_first_of('[', this_row_end_bracket_position+1);
        }

        return builder.done();
    }

private:
    std::string value_to_parse_;
};

}

#endif // __MATRIX_PARSER_H
