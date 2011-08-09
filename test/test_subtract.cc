#include "../test_harness/test.h"
#include "../include/subtract.h"

using namespace osoasso;

Define(Subtract)
{
    It("Subtracts two matrices")
    {
        matrix<double> expected = { { 1.0, -1.0 }, { -0.38, 0.0 } };
        matrix<double> matrix1 = { { 3.14, 1.0 }, { 2.72, 1.0 } };
        matrix<double> matrix2 = { { 2.14, 2.0 }, { 3.10, 1.0 } };

        subtract subtract_command;

        matrix<double> result = subtract_command.call(matrix1, matrix2);

        AssertElementsEqual(expected, result);
    } Done

    It("Throws an exception when called with matrices of two different sizes")
    {
        matrix<double> matrix1 = { { 3.14, 1.0, 3.10 }, { 2.72, 1.0, 9.41} };
        matrix<double> matrix2 = { { 2.14, 2.0 }, { 3.10, 1.0 } };

        subtract subtract_command;

        bool exception_thrown = false;
        try
        {
            subtract_command.call(matrix1, matrix2);
        }
        catch(const std::invalid_argument&)
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
}
