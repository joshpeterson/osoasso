#ifndef __PRINT_MATRIX_H
#define __PRINT_MATRIX_H

#include <ostream>
#include "matrix.h"

namespace osoasso
{

template <typename ValueType>
void print_matrix(const matrix<ValueType>& input, std::ostream& output)
{
    output << "[";
    for (size_t i = 1; i <= input.rows(); ++i)
    {
        for (size_t j = 1; j <= input.columns(); ++j)
        {
            output << input(i, j);
            if (j != input.columns())
                output << " ";
        }
        if (i != input.rows())
            output << "\n";
    }
    output << "]";
}

}

#endif // __PRINT_MATRIX_H
