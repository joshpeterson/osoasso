#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/matrix_parser.h"

using namespace osoasso;

Define(MatrixParser)
{
    It("Parses a vector delimited by [] and spaces")
    {
        matrix<double> expected = { { 3.14, 1, 9.6, 3.5 } };
        //matrix_parser<double> parser("[3.14 1 9.6 3.5]");
        //AssertElementsEqual(expected, *(parser.foo()));
    } Done
}
