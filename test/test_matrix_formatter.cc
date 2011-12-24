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

    It("Can format a matrix to a MathJax string")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        
        matrix_formatter<double> formatter(test_matrix);
        AssertEqual("\\(\\left[\\matrix{3.14&1\\\\2.72&8.9}\\right]\\)", formatter.to_math_jax());
    } Done

    It("Can format a matrix to a HTML table")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        
        matrix_formatter<double> formatter(test_matrix);
        AssertEqual("<table id=\"matrix\"><tr><td>|</td><td>3.14</td><td>1</td><td>|</td></tr><tr><td>|</td><td>2.72</td><td>8.9</td><td>|</td></tr></table>", formatter.to_html_table());
    } Done
}
