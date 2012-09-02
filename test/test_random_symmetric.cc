#include "../test_harness/test.h"
#include "../include/random_symmetric.h"
#include "../include/transpose.h"

using namespace osoasso;

Define(RandomSymmetric)
{
    It("Generates a 2x2 symmetric matrix")
    {
        auto rows = std::shared_ptr<matrix<double>>(new matrix<double>({{2}}));

        random_symmetric random_symmetric_command;

        std::shared_ptr<const matrix<double>> result = random_symmetric_command.call(rows, 1);

        transpose transpose_command;

        AssertElementsEqual(*result, *transpose_command.call(result, 1));
    } Done

    It("Generates a 10x10 symmetric matrix")
    {
        auto rows = std::shared_ptr<matrix<double>>(new matrix<double>({{10}}));

        random_symmetric random_symmetric_command;

        std::shared_ptr<const matrix<double>> result = random_symmetric_command.call(rows, 1);

        transpose transpose_command;

        AssertElementsEqual(*result, *transpose_command.call(result, 1));
    } Done

    It("Throws an exception when called with an input of a size that is not 1,1")
    {
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));

        random_symmetric random_symmetric_command;

        bool exception_thrown = false;
        try
        {
            random_symmetric_command.call(matrix1, 1);
        }
        catch(const std::invalid_argument&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Reports its number of arguments")
    {
        random_symmetric random_symmetric_command;
        
        AssertEqual(1, random_symmetric_command.number_of_arguments());
    } Done

    It("Provides a help message")
    {
        random_symmetric random_symmetric_command;
        
        AssertEqual(std::string("random_symmetric(n) generates a random symmetric matrix of size n x n."), random_symmetric_command.get_help());
    } Done
}
