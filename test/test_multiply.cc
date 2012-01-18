#include "../test_harness/test.h"
#include "../include/multiply.h"

using namespace osoasso;

Define(Multiply)
{
    It("Multiplies two matrices")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{9, 7}, {7, 5}}));
        auto matrix1 = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1}, {2, 1}}));
        auto matrix2 = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2}, {3, 1}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(matrix1, matrix2);

        AssertElementsEqual(*expected, *result);
    } Done
}
