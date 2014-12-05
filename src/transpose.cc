#include "../include/transpose.h"

using namespace osoasso;

expected_const_matrix transpose::call(std::shared_ptr<const matrix<double>> input, int number_of_threads) const
{
    size_t num_rows = input->rows();
    size_t num_columns = input->columns();

    auto result = std::make_shared<matrix<double>>(num_rows, num_columns);
    for (size_t i = 1; i <= num_rows; ++i)
    {
        for (size_t j = 1; j <= num_columns; ++j)
        {
            (*result)(i,j) = (*input)(j, i);
        }
    }

    return expected_const_matrix(result);
}

std::string transpose::get_help() const
{
    return "transpose(A) computes the transpose of matrix A.";
}
