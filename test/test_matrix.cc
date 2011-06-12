#include "../test_harness/test.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(Matrix)
{
    It("Can be created with dimensions")
    {
        matrix<double> test_matrix(3, 3);
        AssertEqual<size_t>(3, test_matrix.rows());
        AssertEqual<size_t>(3, test_matrix.columns());
    } Done

    It("Can be created with dimensions that are not the same")
    {
        matrix<double> test_matrix(2, 4);
        AssertEqual<size_t>(2, test_matrix.rows());
        AssertEqual<size_t>(4, test_matrix.columns());
    } Done

    It("Can be created with and initializer list")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };

        AssertEqual<size_t>(2, test_matrix.rows());
        AssertEqual<size_t>(2, test_matrix.columns());
    } Done

    It("Can be created with and initializer list and dimensions that are not the same")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };

        AssertEqual<size_t>(2, test_matrix.rows());
        AssertEqual<size_t>(3, test_matrix.columns());
    } Done
}
