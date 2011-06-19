#include "../test_harness/test.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MatrixIterator)
{
    It ("Can be dreferenced")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(test_matrix);
        AssertEquals(3.14, *it);
    } Done
}
