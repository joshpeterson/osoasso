#include <sstream>
#include "../test_harness/test.h"
#include "../include/print_matrix.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(PrintMatrix)
{
    It ("Prints a 1x1 matrix")
    {
        matrix<double> input = {{2}};

        std::stringstream output;

        print_matrix(input, output); 

        AssertEqual("[2]", output.str());
    } Done

    It ("Prints a 2x2 matrix")
    {
        matrix<double> input = {{2.2, 3.6}, {4.9, 1.7}};

        std::stringstream output;

        print_matrix(input, output); 

        AssertEqual("[2.2 3.6\n4.9 1.7]", output.str());
    } Done

    It ("Prints a 2x3 matrix")
    {
        matrix<double> input = {{2.2, 3.6, 6.9}, {4.9, 1.7, 0.5}};

        std::stringstream output;

        print_matrix(input, output); 

        AssertEqual("[2.2 3.6 6.9\n4.9 1.7 0.5]", output.str());
    } Done
}
