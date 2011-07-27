#include "../test_harness/test.h"
#include "../include/add.h"

using namespace osoasso;

Define(Add)
{
    It("Adds two matrices")
    {
        matrix<double> matrix1 = { { 3.14, 1.0 }, { 2.72, 8.9 } };
        matrix<double> matrix2 = { { 2.14, 2.0 }, { 3.10, 10.3 } };

        add add_command;

        matrix<double> result = add_command.call(matrix1, matrix2);
    } Done
}
