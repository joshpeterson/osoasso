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
    It ("Finds the eigenvalues of a 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{1, 0, 2}, {0, 2, 1}, {2, 1, 1}}));
        std::vector<double> expected_eigenvalues = { 1.7728, -1.16424, 3.39138 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result.get_value());
    } Done

    It ("Finds the eigenvalues of another 3x3 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2, 4}, {2, 0, 2}, {4, 2, 3}}));
        std::vector<double> expected_eigenvalues = { -1, -1, 8 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result.get_value());
    } Done

    It ("Finds the eigenvalues of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5, 0, 9, 8}, {0, 9, 8, 2}}));
        std::vector<double> expected_eigenvalues = { -9.30949, -7.53826, 8.31277, 16.53498 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result.get_value());
    } Done

    It ("Finds the eigenvalues of a 9x9 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>(
                                                                {{0, 10,  2,  4,  5,  4,  5,  7,  6 },
                                                                {10, 5,  0, 10,  7,  5,  0,  0,  1 },
                                                                {2,  0,  1,  3,  2,  9,  8,  1,  2 },
                                                                {4, 10,  3,  0,  4,  7,  5,  7,  2 },
                                                                {5,  7,  2,  4,  2,  4,  2, 10,  5 },
                                                                {4,  5,  9,  7,  4,  8,  9,  9,  7 },
                                                                {5,  0,  8,  5,  2,  9,  0,  1,  4 },
                                                                {7,  0,  1,  7, 10,  9,  1,  4,  0 },
                                                                {6,  1,  2,  2,  5,  7,  4,  0,  9 }}));

        std::vector<double> expected_eigenvalues = { -16.851612661604428, -8.619305853531, -6.127240802095896,
                                                     -4.479196775842205, -2.8848839841165566, 5.4672217067246915,
                                                     7.7202366055604, 12.772827033874202, 42.001954731030786 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result.get_value());
    } Done

    It ("Throws an exception when the input is not a symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 4}, {2, 0, 2}, {4, 2, 3}}));

        bool exception_occurred = false;
        try
        {
            jacobi_eigen_solver jacobi_command;

            jacobi_command.call(input, 1);
        }
        catch (std::exception&)
        {
            exception_occurred = true;
        }

        AssertTrue(exception_occurred);
    } Done

    It("Provides a help message")
    {
        jacobi_eigen_solver jacobi_command;
        
        AssertEqual(std::string("jacobi_eigen_solver(A) computes the eigen values of a symmetric matrix A."), jacobi_command.get_help());
    } Done
}
