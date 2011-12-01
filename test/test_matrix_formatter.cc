#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/matrix_formatter.h"

using namespace osoasso;

Define(MatrixFormatter)
{
    It("Can format a matrix to a string")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        
        matrix_formatter<double> formatter(test_matrix);
        AssertEqual("[[3.14 1] [2.72 8.9]]", formatter.to_string());
    } Done
}
