#include <math.h>
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

std::shared_ptr<const matrix<double>> jacobi_eigen_solver::call(std::shared_ptr<const matrix<double>> input, int number_of_threads) const
{
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

        auto V = identity_command(A->rows());
        (*V)(i,i) = (*V)(j,j) = std::cos(alpha);
        (*V)(i,j) = std::sin(alpha);
        (*V)(j,i) = -std::sin(alpha);

#ifdef DEBUG_OUTPUT
        std::cout << "V:\n";
        print_matrix(*V, std::cout);
        std::cout << std::endl << std::endl;
#endif

        transpose transpose_command;
        multiply multiply_command;

        auto A_prime = multiply_command.call(multiply_command.call(transpose_command.call(V,1), A, 1), V, 1);

#ifdef DEBUG_OUTPUT
        std::cout << "A_prime:\n";
        print_matrix(*A_prime, std::cout);
        std::cout << std::endl << std::endl;
#endif

        A = A_prime;
    }

    return std::shared_ptr<matrix<double>>(new matrix<double>({{(*A)(1,1)}, {(*A)(2,2)}, {(*A)(3,3)}}));
}

std::string jacobi_eigen_solver::get_help() const
{
    return std::string();
}
