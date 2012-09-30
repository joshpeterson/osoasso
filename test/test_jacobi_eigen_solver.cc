#include "../test_harness/test.h"
#include "../include/jacobi_eigen_solver.h"

using namespace osoasso;

const double threshold = 0.0001;

void validate_eigenvalues(const std::vector<double>& expected_eigenvalues, std::shared_ptr<const matrix<double>> actual_eigenvalues)
{
    for (auto expected_eigenvalue = expected_eigenvalues.begin(); expected_eigenvalue != expected_eigenvalues.end(); ++expected_eigenvalue)
    {
        bool eigenvalue_found = false;
        for (auto actual_eigenvalue = actual_eigenvalues->begin(); actual_eigenvalue != actual_eigenvalues->end() && !eigenvalue_found; ++actual_eigenvalue)
        {
            if (AreEqual(*expected_eigenvalue, *actual_eigenvalue, threshold))
                eigenvalue_found = true;
        }

        if (!eigenvalue_found)
        {
            std::stringstream message;
            message << "The eigenvalue " << *expected_eigenvalue << " was not found in the result: ";
            for (auto it = actual_eigenvalues->begin(); it != actual_eigenvalues->end(); ++it)
            {
                message << *it << " ";
            }
            message << std::endl;

            AssertFail(message.str());
        }
    }
}

Define(JacobiEigenSolver)
{
    It ("Finds the eigenvalues of another 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2, 4}, {2, 0, 2}, {4, 2, 3}}));
        std::vector<double> expected_eigenvalues = { -1, -1, 8 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result);
    } Done

    It ("Finds the eigenvalues of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        std::vector<double> expected_eigenvalues = { 1.7728, -1.16424, 3.39138 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result);
    } Done

    It ("Finds the fourth eigenvalue of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5, 0, 9, 8}, {0, 9, 8, 2}}));
        std::vector<double> expected_eigenvalues = { -9.30949, -7.53826, 8.31277, 16.53498 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result);
    } Done
}
