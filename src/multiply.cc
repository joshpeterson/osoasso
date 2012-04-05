#include <sstream>
#include <stdexcept>
#include <emmintrin.h>
#include "../include/multiply.h"
#include "../include/matrix.h"

#define SSE2_CUSTOM_ASM

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

#if defined(SSE2_INTRINSICS) || defined(SSE2_CUSTOM_ASM)
    std::vector<double, sse2_aligned_allocator<double>> result_sse2;
    result_sse2.reserve(2);
#endif

    size_t result_row_index = 1;
    auto result = std::make_shared<matrix<double>>(left->rows(), right->columns());
    for (auto row = left->row_begin();  row != left->row_end(); ++row)
    {
        size_t result_column_index = 1;
        for (auto column = right->column_begin(); column != right->column_end(); ++column)
        {
#if defined(SSE2_INTRINSICS)
            result_sse2[0] = result_sse2[1] = 0.0;
            multiply_and_add_vector_elements_sse2_intrinsics(*row, *column, &result_sse2[0]);
            (*result)(result_row_index, result_column_index) = result_sse2[0] + result_sse2[1];
#elif defined(SSE2_CUSTOM_ASM)

            size_t size = row->size();
            if (size % 2 != 0)
            {
                size -= 1;
            }

            multiply_and_add_vector_elements_sse2_custom_asm(&(*row)[0], &(*column)[0], size, &result_sse2[0]);

            if (size != row->size())
            {
                result_sse2[0] += (*row)[size] * (*column)[size];
            }

            (*result)(result_row_index, result_column_index) = result_sse2[0] + result_sse2[1];
#else
            (*result)(result_row_index, result_column_index) = multiply_and_add_vector_elements_naive(*row, *column);
#endif
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

void multiply::multiply_and_add_vector_elements_sse2_custom_asm(double* left, double* right, size_t len, double* result) const
{
    //
    // This method assumes len is an even number.
    //
    __asm
	(
        ".intel_syntax noprefix\n"

        // These registers are used to handle the loop.
        "xor eax, eax\n"
        "mov ebx, %[length]\n"

        // Zero xmm2, where we store the result.
		"xorpd xmm2, xmm2\n"

        // Load the result pointer into edi.
		"mov edi, %[result_address]\n"

        // Load the addresses of doubles from the left and right vectors into esi and edx to start the loop.
        "mov edx, %[left_address]\n"
        "mov esi, %[right_address]\n"

        "1:\n"
        // Load the next two doubles from the left vector into xmm4.
        "movapd xmm4, [edx]\n"

        // Load the next two doubles from the right vector into xmm0.
        "movapd xmm0, [esi]\n"

        "add edx, 0x10\n"
        "add esi, 0x10\n"

        // Multiply two doubles.
        "mulpd xmm0, xmm4\n"

        // Accumulate the result of both multiplies into xmm2.
        "addpd xmm2, xmm0\n"

        // Increment the counter and test to see if the loop is done.
        "add eax, 2\n"
        "cmp eax, ebx\n"
        "jnz 1b\n"

        // Move the accumulated result from xmm2 into the result pointer.
		"movapd [edi], xmm2" :: [length] "r" (len), [left_address] "m" (left), [right_address] "m" (right), [result_address] "m" (result) : "%eax", "%ebx", "%edi", "%edx", "%esi"
	);
}

double multiply::multiply_and_add_vector_elements_naive(const std::vector<double, sse2_aligned_allocator<double>>& left,
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

void multiply::multiply_and_add_vector_elements_sse2_intrinsics(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                                const std::vector<double, sse2_aligned_allocator<double>>& right, double* result) const
{
    __m128d result_simd = _mm_load_pd(result);
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

    _mm_store_pd(result, result_simd);

    if (end != left.size())
        *result += left[end] * right[end];
}
