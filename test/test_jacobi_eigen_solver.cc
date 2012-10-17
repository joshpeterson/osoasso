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

    It ("Finds the eigenvalues of a 4x4 symmetric matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{-5, -4, 5, -0}, {-4, 2, 0, 9}, {5, 0, 9, 8}, {0, 9, 8, 2}}));
        std::vector<double> expected_eigenvalues = { -9.30949, -7.53826, 8.31277, 16.53498 };

        jacobi_eigen_solver jacobi_command;

        auto result = jacobi_command.call(input, 1);

        validate_eigenvalues(expected_eigenvalues, result);
    } Done

    It ("Finds the eigenvalues of a 9x9 symmetric matrix")
    {
        /*
Eigenvectors:

 for Eigenvalue -16.851612661604428:
   [ -2.3793453719304165 ; 2.7515997630068014 ; 0.5004220059876988 ; -1.9090570483995346 ; -1.6156414291020567 ; -1.3866756027946499 ; 1.5687665642169262 ; 2.7137528404444966 ; 1 ]

 for Eigenvalue -8.619305853531:
   [ 0.8291953869494905 ; -0.3394372390827966 ; 3.451420158563493 ; 1.5379659347347876 ; -1.7891884778959912 ; -1.5048788588848252 ; -3.188429680266958 ; 1.1571694155230314 ; 1 ]

 for Eigenvalue -6.127240802095896:
   [ -2.0461919021111283 ; -1.56823314443299 ; -0.923461846242972 ; 4.968019281856921 ; 0.449337461441697 ; -3.1827056391231756 ; 2.665320262607508 ; 0.1931746367383375 ; 1 ]

 for Eigenvalue -4.479196775842205:
   [ -158888.0699455987 ; 46663 ; 91943.83562392031 ; -4621.445067475078 ; 161695.83451418785 ; 10409.309876203932 ; -67153.64865245786 ; -69684.16131007545 ; 8850 ]

 for Eigenvalue -2.8848839841165566:
   [ -2.237347355698164 ; 0.47173530902906113 ; -2.218868534532228 ; 1.719417100519072 ; -1.9914010248859972 ; 2.879906308617471 ; -2.0339928317056617 ; 0.27207816836358917 ; 1 ]

 for Eigenvalue 5.4672217067246915:
   [ -0.14855341396345353 ; -1.7112739647128705 ; -0.7829898549097528 ; -0.8267692718107813 ; 1.2326999125986111 ; -0.13504337458292257 ; -0.7322153830633149 ; 1.887338977916785 ; 1 ]

 for Eigenvalue 7.7202366055604:
   [ 0.26649141175008345 ; 0.2561032618196042 ; -0.26999649041566187 ; -0.17318226476825632 ; 0.027158658901540324 ; -0.28530812290479 ; -0.09677351264150992 ; -0.5402324379874599 ; 1 ]

 for Eigenvalue 12.772827033874202:
   [ -0.7195574792251452 ; -1.698715985517247 ; 1.3829348763640248 ; -0.6206755841000704 ; -0.9147098054732661 ; 1.1202947472924079 ; 1.2489637766335264 ; -0.6627485184570292 ; 1 ]

 for Eigenvalue 42.001954731030786:
   [ 1.1510726089685746 ; 1.088476639034733 ; 0.8239673445999701 ; 1.1654865169935806 ; 1.1205774304561764 ; 1.6532260101065888 ; 0.9631663729926233 ; 1.1601470584050897 ; 1 ]
  
         */
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

        validate_eigenvalues(expected_eigenvalues, result);
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
}
