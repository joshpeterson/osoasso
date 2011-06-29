#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/matrix.h"
#include "../include/matrix_builder.h"

using namespace osoasso;

Define(MatrixBuilder)
{
    It("Can create a row vector")
    {
        matrix<double> expected = { { 3.14, 4.2 } };

        matrix_builder<double> test_builder;
        test_builder.add(3.14);
        test_builder.add(4.2);

        AssertElementsEqual(expected, *(test_builder.done()));
    } Done

    It("Can create a column vector")
    {
        matrix<double> expected = { { 3.14 }, { 4.2 } };

        matrix_builder<double> test_builder;
        test_builder.add(3.14);
        test_builder.new_row();
        test_builder.add(4.2);

        AssertElementsEqual(expected, *(test_builder.done()));
    } Done

    It("Can create a 2x2 matrix")
    {
        matrix<double> expected = { { 3.14, 6.24 }, { 4.2, 89.5 } };

        matrix_builder<double> test_builder;
        test_builder.add(3.14);
        test_builder.add(6.24);
        test_builder.new_row();
        test_builder.add(4.2);
        test_builder.add(89.5);

        AssertElementsEqual(expected, *(test_builder.done()));
    } Done

    It("Throws exception for matrix with invalid size")
    {
        matrix_builder<double> test_builder;
        test_builder.add(3.14);
        test_builder.add(6.24);
        test_builder.new_row();
        test_builder.add(4.2);
        test_builder.add(89.5);

        bool exception_occurred = false;
        try
        {
            test_builder.add(89.6);
        }
        catch (std::logic_error&)
        {
            exception_occurred = true;
        }

        AssertTrue(exception_occurred);
    } Done

    It("Throws exception when done is called more than once")
    {
        matrix_builder<double> test_builder;
        test_builder.add(3.14);
        test_builder.done();

        bool exception_occurred = false;
        try
        {
            test_builder.done();
        }
        catch (std::logic_error&)
        {
            exception_occurred = true;
        }

        AssertTrue(exception_occurred);
    } Done
}
