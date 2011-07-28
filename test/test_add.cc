#include "../test_harness/test.h"
#include "../include/add.h"

using namespace osoasso;

Define(Add)
{
    It("Adds two matrices")
    {
        matrix<double> expected = { { 5.28, 3.0 }, { 5.82, 2.0 } };
        matrix<double> matrix1 = { { 3.14, 1.0 }, { 2.72, 1.0 } };
        matrix<double> matrix2 = { { 2.14, 2.0 }, { 3.10, 1.0 } };

        add add_command;

        matrix<double> result = add_command.call(matrix1, matrix2);

        AssertElementsEqual(expected, result);
    } Done

    It("Throws an exception when called with matrices of two different sizes")
    {
        matrix<double> matrix1 = { { 3.14, 1.0, 3.10 }, { 2.72, 1.0, 9.41} };
        matrix<double> matrix2 = { { 2.14, 2.0 }, { 3.10, 1.0 } };

        add add_command;

        bool exception_thrown = false;
        try
        {
            add_command.call(matrix1, matrix2);
        }
        catch(const std::invalid_argument&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Reports its number of arguments")
    {
        add add_command;
        
        AssertEqual(2, add_command.number_of_arguments());
    } Done
}
