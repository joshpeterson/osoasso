#ifndef __MATRIX_PARSER_H
#define __MATRIX_PARSER_H

#include <string>
#include <memory>

namespace osoasso
{

template <typename ValueType>
class matrix_parser
{
public:
    matrix_parser(std::string value_to_parse)
    {
    }

    /*
    std::shared_ptr<matrix<ValueType>> foo() const
    {
        matrix<double>* matrix_parsed = new matrix<double>({ { 3.14, 1.0, 9.6, 3.5 } });
        return matrix_parsed;
    }
    */
};

}

#endif // __MATRIX_PARSER_H
