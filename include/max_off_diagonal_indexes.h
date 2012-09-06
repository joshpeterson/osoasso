#ifndef __MAX_OFF_DIAGONAL_INDEXES_H
#define __MAX_OFF_DIAGONAL_INDEXES_H

#include <vector>
#include <memory>
#include <cmath>
#include "matrix.h"

namespace osoasso
{

template <typename ValueType>
std::vector<int> max_off_diagonal_indexes(const matrix<ValueType>& input)
{
    std::vector<int> indexes(input.rows());

    for (size_t i = 1; i <= input.rows(); ++i)
    {
        ValueType maximum_value_in_row = ValueType();
        for (size_t j = 1; j <= input.columns(); ++j)
        {
            if (i != j && std::abs(input(i,j)) > std::abs(maximum_value_in_row))
                indexes[i-1] = j;
        }
    }

    return indexes;
}

}

#endif // __MAX_OFF_DIAGONAL_INDEXES_H
