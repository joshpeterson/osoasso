#include "../test_harness/test.h"
#include "../include/matrix_row_iterator.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MatrixRowIterator)
{
    It ("Can be dreferenced")
    {
        std::vector<double> expected_row = { 3.14, 1.0 };

        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix_row_iterator<double>(&test_matrix);

        AssertElementsEqual(expected_row, *it);
    } Done
}
