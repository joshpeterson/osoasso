#include "../test_harness/test.h"
#include "../include/subtract.h"

using namespace osoasso;

Define(Subtract)
{
    It("Subtracts two matrices")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{1.0, -1.0}, {-0.38, 0.0}}));
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0}, {2.72, 1.0 }}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0}}));

        subtract subtract_command;

        std::shared_ptr<const matrix<double>> result = subtract_command.call(matrix1, matrix2, 1).get_value();

        AssertElementsEqual(*expected, *result);
    } Done

    It("Throws an exception when called with matrices of two different sizes")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0 }}));

        subtract subtract_command;

        bool exception_thrown = false;
        try
        {
            subtract_command.call(matrix1, matrix2, 1).get_value();
        }
        catch(const std::runtime_error&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Reports its number of arguments")
    {
        subtract subtract_command;
        
        AssertEqual(2, subtract_command.number_of_arguments());
    } Done

    It("Provides a help message")
    {
        subtract subtract_command;

        AssertEqual(std::string("subtract(A,B) computes the difference of two matrices m x n A and B, with A on the left."), subtract_command.get_help());
    } Done
}
