#include "../test_harness/test.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(MatrixIterator)
{
    It ("Can be dreferenced")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        AssertEqual(3.14, *it);
    } Done

    It ("Can be post incremented")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        it++;
        AssertEqual(1.0, *it);
    } Done

    It ("Can be post incremented to the second row")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        it++;
        it++;
        AssertEqual(2.72, *it);
    } Done

    It ("Returns the previous value for post increment")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        AssertEqual(3.14, *(it++));
    } Done

    It ("Can be pre incremented")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        ++it;
        AssertEqual(1.0, *it);
    } Done

    It ("Can be pre incremented to the second row")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        ++it;
        ++it;
        AssertEqual(2.72, *it);
    } Done

    It ("Returns the new value for pre increment")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        AssertEqual(1.0, *(++it));
    } Done

    It ("Can be default constructed")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        matrix<double>::iterator it;
    } Done

    It ("Can be compared to another iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        auto it2 = matrix<double>::iterator(&test_matrix);

        AssertTrue(it.equal(it2));
    } Done

    It ("Can be compared to a different iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        auto it2 = matrix<double>::iterator(&test_matrix);

        ++it2;

        AssertFalse(it.equal(it2));
    } Done

    It ("Can be compared to a default constructed iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        matrix<double>::iterator it; 
        matrix<double>::iterator it2; 

        AssertTrue(it.equal(it2));
    } Done

    It ("Is not equal to a default constructed iterator when it is not default constructed")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        matrix<double>::iterator it2; 

        AssertFalse(it.equal(it2));
    } Done

    It ("Can be compared to another iterator with the equality operator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        auto it2 = matrix<double>::iterator(&test_matrix);

        AssertTrue(it == it2);
    } Done

    It ("Can be iterated to the end iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        auto it = matrix<double>::iterator(&test_matrix);
        matrix<double>::iterator end;

        ++it;
        ++it;
        ++it;
        ++it;

        AssertTrue(it == end);
    } Done
}
