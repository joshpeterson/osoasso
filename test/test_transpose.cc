#include "../test_harness/test.h"
#include "../include/transpose.h"

using namespace osoasso;

Define(Transpose)
{
    It("Provides the transpose of a 2x2 matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1}, {2, 4}}));
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2}, {1, 4}}));

        transpose transpose_command;

        std::shared_ptr<const matrix<double>> result = transpose_command.call(input, input, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Provides the transpose of a 3x3 matrix")
    {
        auto input = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 8}, {2, 4, 6}, {1, 1, 9}}));
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 2, 1}, {1, 4, 1}, {8, 6, 9}}));

        transpose transpose_command;

        std::shared_ptr<const matrix<double>> result = transpose_command.call(input, input, 1);

        AssertElementsEqual(*expected, *result);
    } Done
}
