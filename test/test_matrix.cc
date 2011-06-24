#include <stdexcept>
#include <iostream>
#include "../test_harness/test.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(Matrix)
{
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

    It("Throws an exception when created with invalid dimensions")
    {
        bool exception_occurred = false;
        try
        {
            matrix<double> test_matrix = { { 3.14, 1.0 }, { 2.72, 8.9, 5.42} };
        }
        catch (const std::invalid_argument&)
        {
            exception_occurred = true;
        }
        
        AssertTrue(exception_occurred);
    } Done

    It("Can be indexed")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        AssertEqual(3.14, test_matrix(1,1));
    } Done

    It("Can be indexed with different row and column indexes")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        AssertEqual(5.42, test_matrix(2,3));
    } Done

    It("Throws an exception for a large column index")
    {
        bool exception_occurred = false;
        try
        {
            matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
            test_matrix(1,4);
        }
        catch (const std::invalid_argument&)
        {
            exception_occurred = true;
        }
        AssertTrue(exception_occurred);
    } Done

    It("Throws an exception for a large row index")
    {
        bool exception_occurred = false;
        try
        {
            matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
            test_matrix(5,3);
        }
        catch (const std::invalid_argument&)
        {
            exception_occurred = true;
        }
        AssertTrue(exception_occurred);
    } Done

    It("Throws an exception for a zero column index")
    {
        bool exception_occurred = false;
        try
        {
            matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
            test_matrix(1,0);
        }
        catch (const std::invalid_argument&)
        {
            exception_occurred = true;
        }
        AssertTrue(exception_occurred);
    } Done

    It("Throws an exception for a zero row index")
    {
        bool exception_occurred = false;
        try
        {
            matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
            test_matrix(0,2);
        }
        catch (const std::invalid_argument&)
        {
            exception_occurred = true;
        }
        AssertTrue(exception_occurred);
    } Done

    It("Provides a starting iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        auto it = test_matrix.begin();

        AssertEqual(3.14, *it);
    } Done

    It("Provides an ending iterator")
    {
        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };
        auto it = test_matrix.end();
    } Done

    It("Can be iterated")
    {
        std::vector<double> expected = { 3.14, 1.0, 3.19, 2.72, 8.9, 5.42 };
        std::vector<double> actual;

        matrix<double> test_matrix = { { 3.14, 1.0, 3.19 }, { 2.72, 8.9, 5.42} };

        std::copy(test_matrix.begin(), test_matrix.end(), std::back_inserter(actual));

        AssertElementsEqual(expected, actual);
    } Done
}
