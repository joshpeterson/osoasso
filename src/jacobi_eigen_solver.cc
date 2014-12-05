#include <math.h>
#include <stdexcept>
#include "../include/jacobi_eigen_solver.h"
#include "../include/max_off_diagonal_index.h"
#include "../include/identity.h"
#include "../include/transpose.h"
#include "../include/multiply.h"
#include "../include/print_matrix.h"

//#define DEBUG_OUTPUT
#ifdef DEBUG_OUTPUT
#include <iostream>
#endif

using namespace osoasso;

expected_const_matrix jacobi_eigen_solver::call(std::shared_ptr<const matrix<double>> input, int number_of_threads) const
{
    transpose transpose_command;
    auto input_transpose = transpose_command.call(input, 1).get_value();
    if (*input != *input_transpose)
        INVALID_ARGUMENT_CONST(std::invalid_argument("The input matrix is not a symmetric matrix. This command requires a symmetric matrix."));

    std::shared_ptr<const matrix<double>> A = input;
#ifdef DEBUG_OUTPUT
    int iteration = 0;
#endif
    while(true)
    {
        auto max_off_diagonal_index = find_max_off_diagonal_index(*A);
        auto i = max_off_diagonal_index.first;
        auto j = max_off_diagonal_index.second;

        if (std::abs((*A)(i,j) - 0.0) < 0.0001)
            break;

#ifdef DEBUG_OUTPUT
        ++iteration;
        std::cout << std::endl << "Iteration: " << iteration << std::endl << std::endl;

        std::cout << "A:\n";
        print_matrix(*A, std::cout);
        std::cout << std::endl << std::endl;

        std::cout << "Max index: (" << i << "," << j << ") value: " << (*A)(i,j) << std::endl << std::endl;
#endif

        double alpha = 0.5 * std::atan2(2.0 * (*A)(i,j), ((*A)(j,j) - (*A)(i,i)));

#ifdef DEBUG_OUTPUT
        std::cout << "alpha: " << alpha << std::endl << std::endl;
#endif

        identity identity_command;

        auto V = identity_command(A->rows()).get_value();
        (*V)(i,i) = (*V)(j,j) = std::cos(alpha);
        (*V)(i,j) = std::sin(alpha);
        (*V)(j,i) = -std::sin(alpha);

#ifdef DEBUG_OUTPUT
        std::cout << "V:\n";
        print_matrix(*V, std::cout);
        std::cout << std::endl << std::endl;
#endif

        multiply multiply_command;

        auto A_prime = multiply_command.call(multiply_command.call(transpose_command.call(V,1).get_value(), A, 1).get_value(), V, 1).get_value();

#ifdef DEBUG_OUTPUT
        std::cout << "A_prime:\n";
        print_matrix(*A_prime, std::cout);
        std::cout << std::endl << std::endl;
#endif

        A = A_prime;
    }

    auto eigenvalues = std::shared_ptr<matrix<double>>(new matrix<double>(1, input->rows()));

    for (size_t i = 1; i <= input->rows(); ++i)
        (*eigenvalues)(1, i) = (*A)(i,i);

    return expected_const_matrix(eigenvalues);
}

std::string jacobi_eigen_solver::get_help() const
{
    return "jacobi_eigen_solver(A) computes the eigen values of a symmetric matrix A.";
}
