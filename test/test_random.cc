#include "../test_harness/test.h"
#include "../include/random.h"

using namespace osoasso;

Define(Random)
{
    It("Generates a random square matrix of a given size")
    {
        auto rows = std::shared_ptr<matrix<double>>(new matrix<double>({{3}}));
        auto columns = std::shared_ptr<matrix<double>>(new matrix<double>({{3}}));

        random random_command;

        std::shared_ptr<const matrix<double>> result = random_command.call(rows, columns);

        AssertEqual<size_t>(3, result->rows());
        AssertEqual<size_t>(3, result->columns());
    } Done

    It("Generates a random matrix of a given size with a different number of rows and columns")
    {
        auto rows = std::shared_ptr<matrix<double>>(new matrix<double>({{2}}));
        auto columns = std::shared_ptr<matrix<double>>(new matrix<double>({{5}}));

        random random_command;

        std::shared_ptr<const matrix<double>> result = random_command.call(rows, columns);

        AssertEqual<size_t>(2, result->rows());
        AssertEqual<size_t>(5, result->columns());
    } Done

    It("Throws an exception when called with a first input of a size that is not 1,1")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2}}));

        random random_command;

        bool exception_thrown = false;
        try
        {
            random_command.call(matrix1, matrix2);
        }
        catch(const std::invalid_argument&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Throws an exception when called with a second input of a size that is not 1,1")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{2}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));

        random random_command;

        bool exception_thrown = false;
        try
        {
            random_command.call(matrix1, matrix2);
        }
        catch(const std::invalid_argument&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Reports its number of arguments")
    {
        random random_command;
        
        AssertEqual(2, random_command.number_of_arguments());
    } Done

    It("Provides a help message")
    {
        random random_command;
        
        AssertEqual(std::string("random(m,n) generates a random matrix of size m x n."), random_command.get_help());
    } Done
}
