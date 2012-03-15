#include <sstream>
#include <stdexcept>
#include "../include/multiply.h"
#include "../include/matrix.h"

using namespace osoasso;

std::shared_ptr<const matrix<double>> multiply::call(std::shared_ptr<const matrix<double>> left,
                                                     std::shared_ptr<const matrix<double>> right) const
{
    if (left->columns() != right->rows())
    {
        std::stringstream message;
        message << "The number of columns in the left metrix (" << left->columns()
                << ") is not the same as the number of rows in the right matrix ("
                << right->rows() << ").";
        throw std::invalid_argument(message.str());
    }

    size_t result_row_index = 1;
    auto result = std::make_shared<matrix<double>>(left->rows(), right->columns());
    for (auto row = left->row_begin();  row != left->row_end(); ++row)
    {
        size_t result_column_index = 1;
        for (auto column = right->column_begin(); column != right->column_end(); ++column)
        {
            (*result)(result_row_index, result_column_index) = multiply_and_add_vector_elements(*row, *column);
            ++result_column_index;
        }
        ++result_row_index;
    }

    return result;
}

int multiply::number_of_arguments() const
{
    return 2;
}

std::string multiply::get_help() const
{
    return "multiply(A,B) computes the product of two matrices A (m x n) and B (n x p), with A on the left.";
}

double multiply::multiply_and_add_vector_elements(const std::vector<double>& left, const std::vector<double>& right) const
{
    auto end = left.end();

    auto left_it = left.begin();
    auto right_it = right.begin();

    double result = 0.0;
    while (left_it != end)
    {
        result += *left_it * *right_it;

        ++left_it;
        ++right_it;
    }

    return result;
}
