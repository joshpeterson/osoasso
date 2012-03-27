#ifndef __MULTIPLY_H
#define __MULTIPLY_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command.h"

namespace osoasso
{

class multiply : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const;
    int number_of_arguments() const;
    std::string get_help() const;

private:
    double multiply_and_add_vector_elements_naive(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                  const std::vector<double, sse2_aligned_allocator<double>>& right) const;

    void multiply_and_add_vector_elements_sse2_intrinsics(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                          const std::vector<double, sse2_aligned_allocator<double>>& right, double* result) const;

    void multiply_and_add_vector_elements_sse2_custom_asm(const std::vector<double, sse2_aligned_allocator<double>>& left,
                                                          const std::vector<double, sse2_aligned_allocator<double>>& right,
                                                          size_t size, double* result) const;
};

}

#endif // __MULTIPLY_H
