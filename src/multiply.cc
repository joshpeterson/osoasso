#include <sstream>
#include <stdexcept>
#include <emmintrin.h>
#include "../include/multiply.h"
#include "../include/matrix.h"
#include "../include/parallel_task.h"

#define SSE2_CUSTOM_ASM

using namespace osoasso;

std::shared_ptr<const matrix<double>> multiply::call(std::shared_ptr<const matrix<double>> left, std::shared_ptr<const matrix<double>> right,
                                                     int number_of_threads) const
{
    if (left->columns() != right->rows())
    {
        std::stringstream message;
        message << "The number of columns in the left metrix (" << left->columns()
                << ") is not the same as the number of rows in the right matrix ("
                << right->rows() << ").";
        throw std::invalid_argument(message.str());
    }

    row_multiplier multiplier(left->rows(), right->columns());

    auto task = make_parallel_task(left->row_begin(), right->row_end(), multiplier, right, number_of_threads);
    task.start();
    task.complete();

    return multiplier.get_result();
}

int multiply::number_of_arguments() const
{
    return 2;
}

std::string multiply::get_help() const
{
    return "multiply(A,B) computes the product of two matrices A (m x n) and B (n x p), with A on the left.";
}

row_multiplier::row_multiplier(std::shared_ptr<const matrix<double>> right) : right_(right), task_results_()
{
}

row_multiplier::row_multiplier(size_t rows, size_t columns) : rows_(rows), current_row_(1), columns_(columns), current_column_(1)
{
    result_matrix_ = std::make_shared<matrix<double>>(rows_, columns_);
}

template <typename IteratorType>
void row_multiplier::map(IteratorType begin, IteratorType end)
{
#if defined(SSE2_CUSTOM_ASM)
    std::vector<double, sse2_aligned_allocator<double>> result_sse2;
    result_sse2.reserve(2);
#endif

    for (auto row = begin; row != end; ++row)
    {
        for (auto column = right_->column_begin(); column != right_->column_end(); ++column)
        {
#if defined(SSE2_CUSTOM_ASM)
            result_sse2[0] = result_sse2[1] = 0.0;

            size_t size = row->size();
            size_t leftover = size % 4;
            if (leftover != 0)
            {
                size -= leftover;
            }

            if (size >= 4)
                multiply_and_add_vector_elements_sse2_custom_asm(&(*row)[0], &(*column)[0], size, &result_sse2[0]);

            for (int i = leftover-1; i >= 0; i--)
            {
                result_sse2[0] += (*row)[size + i] * (*column)[size + i];
            }

            task_results_.push_back(result_sse2[0] + result_sse2[1]);
#else
            task_results_.push_back(multiply_and_add_vector_elements_naive(*row, *column));
#endif
        }
    }
}

void row_multiplier::reduce(const row_multiplier& other)
{
    for (auto result = other.task_results_.begin(); result != other.task_results_.end(); ++result)
    {
        (*result_matrix_)(current_row_, current_column_) = *result;
        if (current_column_ == columns_)
        {
            ++current_row_;
            current_column_ = 1;
        }
        else
        {
            ++current_column_;
        }
    }
}

std::shared_ptr<const matrix<double>> row_multiplier::get_result() const
{
    return result_matrix_;
}

void row_multiplier::multiply_and_add_vector_elements_sse2_custom_asm(double* left, double* right, size_t len, double* result) const
{
    //
    // This method assumes len is a multiple of four.
    //
    __asm
	(
        ".intel_syntax noprefix\n"

        // These registers are used to handle the loop.
        "xor eax, eax\n"
        "mov ebx, %[length]\n"

        // Zero xmm2 and xmm3, where we store the result.
		"xorpd xmm2, xmm2\n"

        // Load the result pointer into edi.
		"mov edi, %[result_address]\n"

        // Load the addresses of doubles from the left and right vectors into edx and esi to start the loop.
        "mov edx, %[left_address]\n"
        "mov esi, %[right_address]\n"

        "1:\n"

        "prefetchnta [edx+0x20]\n"
        "prefetchnta [esi+0x20]\n"

        // Load the next four doubles from the left vector into xmm3 and xmm4.
        "movapd xmm3, [edx]\n"
        "movapd xmm4, [edx+0x10]\n"

        // Load the next four doubles from the right vector into xmm0 and xmm1.
        "movapd xmm0, [esi]\n"
        "movapd xmm1, [esi+0x10]\n"

        // Multiply four doubles.
        "mulpd xmm0, xmm3\n"
        "mulpd xmm1, xmm4\n"

        // Accumulate the result of both multiplies into xmm2.
        "addpd xmm2, xmm0\n"
        "addpd xmm2, xmm1\n"

        // Increment the pointers for the next loop.
        "add edx, 0x20\n"
        "add esi, 0x20\n"

        // Increment the counter and test to see if the loop is done.
        "add eax, 4\n"
        "cmp eax, ebx\n"
        "jnz 1b\n"

        // Move the accumulated result from xmm2 into the result pointer.
		"movapd [edi], xmm2" :: [length] "r" (len), [left_address] "m" (left), [right_address] "m" (right), [result_address] "m" (result) : "%eax", "%ebx", "%edi", "%edx", "%esi"
	);
}

double row_multiplier::multiply_and_add_vector_elements_naive(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                              const std::vector<double, sse2_aligned_allocator<double>>& right) const
{
    double result = 0.0;

    auto end = left.end();

    auto left_it = left.begin();
    auto right_it = right.begin();

    while(left_it != end)
    {
        result += *left_it * *right_it;
        ++left_it;
        ++right_it;
    }

    return result;
}

