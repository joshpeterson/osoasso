#ifndef __MATRIX_FORMATTER_H
#define __MATRIX_FORMATTER_H

#include <string>
#include <sstream>
#include "matrix.h"

namespace osoasso
{

template <typename ValueType>
class matrix_formatter
{
public:
    matrix_formatter(const typename osoasso::matrix<ValueType>& matrix_to_format) 
       : matrix_to_format_(matrix_to_format)
    {
    }

    std::string to_string() const
    {
        std::stringstream matrix_string;

        matrix_string << "[";

        int rows = matrix_to_format_.rows();
        int columns = matrix_to_format_.columns();
        for (int i = 1; i <= rows; ++i)
        {
            matrix_string << "[";
            for (int j = 1; j <= columns; ++j)
            {
                matrix_string << matrix_to_format_(i,j);
                if (j != columns)
                    matrix_string << " ";
            }
            matrix_string << "]";

            if (i != rows)
                matrix_string << " ";
        }

        matrix_string << "]";

        return matrix_string.str();
    }

private:
    const osoasso::matrix<ValueType>& matrix_to_format_;
};

}

#endif // __MATRIX_FORMATTER_H
