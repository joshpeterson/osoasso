#include "../test_harness/test.h"
#include "../include/jacobi_eigen_solver.h"

using namespace osoasso;

Define(JacobiEigenSolver)
{
    It ("Finds the eigenvalues of a 3x3 matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{1.7728}, {-1.16424}, {3.39138}}));

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        AssertElementsEqual(*expected, *result, 0.0001);
    } Done
}
