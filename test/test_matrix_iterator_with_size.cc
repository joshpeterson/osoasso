#include "../test_harness/test.h"
#include "../include/matrix_iterator_with_size.h"

using namespace osoasso;

Define(MatrixIteratorWithSize)
{
    It("Returns the number of rows in the matrix first")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        matrix_iterator_with_size<double> test_iterator(&test_matrix);

        AssertEqual<double>(2, *test_iterator);
    } Done

    It("Returns the number of columns in the matrix second")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        matrix_iterator_with_size<double> test_iterator(&test_matrix);

        test_iterator++;

        AssertEqual<double>(3, *test_iterator);
    } Done

    It("Returns the first entry in the matrix third")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        matrix_iterator_with_size<double> test_iterator(&test_matrix);

        test_iterator++;
        test_iterator++;

        AssertEqual<double>(3.14, *test_iterator);
    } Done

    It ("Can be iterated to the end iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        matrix_iterator_with_size<double> test_iterator(&test_matrix);
        matrix_iterator_with_size<double> end;

        ++test_iterator;
        ++test_iterator;
        ++test_iterator;
        ++test_iterator;
        ++test_iterator;
        ++test_iterator;
        ++test_iterator;
        ++test_iterator;

        AssertTrue(test_iterator == end);
    } Done
}
