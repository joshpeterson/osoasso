#include "../test_harness/test.h"
#include "../include/jacobi_eigen_solver.h"

using namespace osoasso;

const double threshold = 0.0001;

void find_eigenvalue(std::shared_ptr<matrix<double>> input, double eigenvalue)
{
    jacobi_eigen_solver jacobi_command;

    auto result = jacobi_command.call(input, 1);

    bool eigenvalue_found = false;
    for (auto it = result->begin(); it != result->end() && !eigenvalue_found; ++it)
    {
        if (AreEqual(eigenvalue, *it, threshold))
            eigenvalue_found = true;
    }

    if (!eigenvalue_found)
    {
        std::stringstream message;
        message << "The eigenvalue " << eigenvalue << " was not found in the result: ";
        for (auto it = result->begin(); it != result->end(); ++it)
        {
            message << *it << " ";
        }
        message << std::endl;

        AssertFail(message.str());
    }
}

Define(JacobiEigenSolver)
{
    It ("Finds the first eigenvalue of a 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        find_eigenvalue(input, 1.7728);
    } Done

    It ("Finds the second eigenvalue of a 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        find_eigenvalue(input, -1.16424);
    } Done

    It ("Finds the third eigenvalue of a 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        find_eigenvalue(input, 3.39138);
    } Done

    It ("Finds the first unique eigenvalue of another 3x3 symmetric matrix")
    {
        // This matrix has eigenvalues of -1, -1, and 8
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2, 4}, {2, 0, 2}, {4, 2, 3}}));
        find_eigenvalue(input, -1);
    } Done

    It ("Finds the second unique eigenvalue of another 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2, 4}, {2, 0, 2}, {4, 2, 3}}));
        find_eigenvalue(input, 8);
    } Done

    It ("Finds the first eigenvalue of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5,0,9,8}, {0, 9, 8, 2}}));
        find_eigenvalue(input, -9.30949);
    } Done

    It ("Finds the second eigenvalue of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5,0,9,8}, {0, 9, 8, 2}}));
        find_eigenvalue(input, -7.53826);
    } Done

    It ("Finds the third eigenvalue of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5,0,9,8}, {0, 9, 8, 2}}));
        find_eigenvalue(input, 8.31277);
    } Done

    It ("Finds the fourth eigenvalue of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5,0,9,8}, {0, 9, 8, 2}}));
        find_eigenvalue(input, 16.53498);
    } Done
}
