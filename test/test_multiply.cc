#include "../test_harness/test.h"
#include "../include/multiply.h"

using namespace osoasso;

Define(Multiply)
{
    It("Multiplies two 2x2 square matrices")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{9, 7}, {7, 5}}));
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1}, {2, 1}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2}, {3, 1}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 3x3 square matrices")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{11, 11, 16}, {11, 13, 20}, {24, 21, 43}}));
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2}, {2, 1, 4}, {1, 5, 7}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2}, {3, 1, 4}, {1, 2, 3}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies matrices of different sizes")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{47, 37}, {81, 43}}));
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 4}, {2, 1, 8}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 6}, {5, 7}, {9, 3}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Throws an exception when called with matrices of invalid sizes")
    {
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0}}));

        multiply multiply_command;

        bool exception_thrown = false;
        std::string message;
        try
        {
            multiply_command.call(left, right);
        }
        catch(const std::invalid_argument& e)
        {
            exception_thrown = true;
            message = e.what();
        }

        AssertTrue(exception_thrown);
        AssertEqual(std::string("The number of columns in the left metrix (3) is not the same as the number of rows in the right matrix (2)."), message);
    } Done

    It("Reports its number of arguments")
    {
        multiply multiply_command;
        
        AssertEqual(2, multiply_command.number_of_arguments());
    } Done

    It("Provides a help message")
    {
        multiply multiply_command;
        
        AssertEqual(std::string("multiply(A,B) computes the product of two matrices A (m x n) and B (n x p), with A on the left."), multiply_command.get_help());
    } Done
}
