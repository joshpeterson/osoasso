#include <sstream>
#include <stdexcept>
#include <emmintrin.h>
#include "../include/multiply.h"
#include "../include/matrix.h"

#include <iostream>

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

double multiply::multiply_and_add_vector_elements(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                  const std::vector<double, sse2_aligned_allocator<double>>& right) const
{
    std::vector<double, sse2_aligned_allocator<double>> result(2);

    __m128d result_simd = _mm_load_pd(&result[0]);
    size_t end = left.size();
	if (end % 2 != 0)
		end -= 1;
    for (size_t i = 0; i < end; i+=2)
    {
        __m128d left_simd = _mm_load_pd(&left[i]);
        __m128d right_simd = _mm_load_pd(&right[i]);
        __m128d product_simd = _mm_mul_pd(left_simd, right_simd);
        result_simd = _mm_add_pd(result_simd, product_simd);
    }

    _mm_store_pd(&result[0], result_simd);

	if (end != left.size())
		result[1] += left[end] * right[end];

    return result[0] + result[1];
}
