#ifndef __MAX_OFF_DIAGONAL_INDEX_H
#define __MAX_OFF_DIAGONAL_INDEX_H

#include <vector>
#include <utility>
#include <cmath>
#include "matrix.h"
#include "utility.h"

namespace osoasso
{

template <typename ValueType>
std::pair<size_t, size_t> find_max_off_diagonal_index(const matrix<ValueType>& input)
{
    size_t row_index_For_maximum_value = 0;
    size_t column_index_For_maximum_value = 0;

    ValueType maximum_value = ValueType();
    for (size_t i = 1; i <= input.rows(); ++i)
    {
        for (size_t j = 1; j <= input.columns(); ++j)
        {
            double current_value = std::abs(input(i,j));
            if (i != j && (!double_equal(current_value, maximum_value) && current_value > maximum_value))
            {
                maximum_value = current_value;
                row_index_For_maximum_value = i;
                column_index_For_maximum_value = j;
            }
        }
    }

    return std::make_pair(row_index_For_maximum_value, column_index_For_maximum_value);
}

}

#endif // __MAX_OFF_DIAGONAL_INDEX_H
