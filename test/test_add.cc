#include "../test_harness/test.h"
#include "../include/add.h"

using namespace osoasso;

Define(Add)
{
    It("Adds two matrices")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{5.28, 3.0}, {5.82, 2.0}}));
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0}, {2.72, 1.0}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0}}));

        add add_command;

        std::shared_ptr<const matrix<double>> result = add_command.call(matrix1, matrix2);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Throws an exception when called with matrices of two different sizes")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0}}));

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

    It("Provides a help message")
    {
        add add_command;

        AssertEqual(std::string("add(A,B) computes the sum of two matrices m x n A and B."), add_command.get_help());
    } Done
}
