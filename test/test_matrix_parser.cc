#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/matrix_parser.h"

using namespace osoasso;

Define(MatrixParser)
{
    It("Parses a row vector delimited by [] and spaces")
    {
        matrix<double> expected = { { 3.14, 1, 9.6, 3.5 } };
        matrix_parser<double> parser("[[3.14 1 9.6 3.5]]");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done

    It("Parses a column vector delimited by [] and spaces")
    {
        matrix<double> expected = { { 3.14 }, { 1 } };
        matrix_parser<double> parser("[[3.14] [1]]");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done

    It("Parses a square matrix delimited by [] and spaces")
    {
        matrix<double> expected = { { 3.14, 9.6, 3.5 }, { 2.10, 0, 80.2 }, { 1.1, 0.2, 31.6 } };
        matrix_parser<double> parser("[[3.14 9.6 3.5] [2.10 0 80.2] [1.1 0.2 31.6]]");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done

    It("Parses a column vector with leading and trailing whitespace")
    {
        matrix<double> expected = { { 3.14 }, { 1 } };
        matrix_parser<double> parser(" [[3.14] [1]] ");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done

    It("Parses a column vector with embedded leading and trailing whitespace")
    {
        matrix<double> expected = { { 3.14 }, { 1 } };
        matrix_parser<double> parser("[ [3.14]   [1] ]");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done
    
    It("Parses a row vector with extra white space between values")
    {
        matrix<double> expected = { { 3.14, 1, 9.6, 3.5 } };
        matrix_parser<double> parser("[[ 3.14   1  9.6 3.5 ]]");

        AssertElementsEqual(expected, *(parser.parse()));
    } Done
}
