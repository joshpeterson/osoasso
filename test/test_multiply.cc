#include "../test_harness/test.h"
#include "../include/multiply.h"

using namespace osoasso;

Define(Multiply)
{
    It("Multiplies matrices of different sizes")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{47, 37}, {81, 43}}));
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 4}, {2, 1, 8}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 6}, {5, 7}, {9, 3}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Throws an exception when called with matrices of invalid sizes")
    {
        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3.14, 1.0, 3.10},
                                                                           {2.72, 1.0, 9.41}}));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2.14, 2.0}, {3.10, 1.0}}));

        multiply multiply_command;

        bool exception_thrown = false;
        std::string message;
        try
        {
            multiply_command.call(left, right, 1);
        }
        catch(const std::invalid_argument& e)
        {
            exception_thrown = true;
            message = e.what();
        }

        AssertTrue(exception_thrown);
        AssertEqual(std::string("The number of columns in the left metrix (3) is not the same as the number of rows in the right matrix (2)."), message);
    } Done

    It("Reports its number of arguments")
    {
        multiply multiply_command;
        
        AssertEqual(2, multiply_command.number_of_arguments());
    } Done

    It("Provides a help message")
    {
        multiply multiply_command;
        
        AssertEqual(std::string("multiply(A,B) computes the product of two matrices A (m x n) and B (n x p), with A on the left."), multiply_command.get_help());
    } Done

    It("Multiplies two 2x2 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{9, 7},
                                                                            {7, 5}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1},
                                                                        {2, 1}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2},
                                                                         {3, 1}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 3x3 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{11, 11, 16},
                                                                            {11, 13, 20},
                                                                            {24, 21, 43}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2},
                                                                        {2, 1, 4},
                                                                        {1, 5, 7}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2},
                                                                         {3, 1, 4},
                                                                         {1, 2, 3}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 4x4 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{15, 19, 28, 27	},
	                                                                        {19, 29, 44, 45	},
	                                                                        {29, 31, 58, 59	},
	                                                                        {24, 19, 39, 19	}}));
                    

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4},
                                                                        {2, 1, 4, 8},
                                                                        {1, 5, 7, 5},
                                                                        {2, 5, 0, 5}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2},
                                                                         {3, 1, 4, 1},
                                                                         {1, 2, 3, 6},
                                                                         {1, 2, 3, 2}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 5x5 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{17, 23, 34, 35, 40},
                                                                            {21, 33, 50, 53, 55},
                                                                            {31, 35, 64, 67, 64},
                                                                            {26, 23, 45, 27, 46},
                                                                            {20, 28, 46, 50, 55}}));
        
                    

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2},
                                                                        {2, 1, 4, 8, 2},
                                                                        {1, 5, 7, 5, 2},
                                                                        {2, 5, 0, 5, 2},
                                                                        {1, 2, 3, 4, 5}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3},
                                                                         {3, 1, 4, 1, 3},
                                                                         {1, 2, 3, 6, 3},
                                                                         {1, 2, 3, 2, 3},
                                                                         {1, 2, 3, 4, 5}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 6x6 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{20, 29, 43, 47, 55, 66},
                                                                            {24, 39, 59, 65, 70, 86},
                                                                            {34, 41, 73, 79, 79, 98},
                                                                            {29, 29, 54, 39, 61, 74},
                                                                            {23, 34, 55, 62, 70, 78},
                                                                            {26, 40, 64, 74, 85, 96}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3},
                                                                        {2, 1, 4, 8, 2, 3},
                                                                        {1, 5, 7, 5, 2, 3},
                                                                        {2, 5, 0, 5, 2, 3},
                                                                        {1, 2, 3, 4, 5, 3},
                                                                        {1, 2, 3, 4, 5, 6}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4},
                                                                         {3, 1, 4, 1, 3, 4},
                                                                         {1, 2, 3, 6, 3, 4},
                                                                         {1, 2, 3, 2, 3, 4},
                                                                         {1, 2, 3, 4, 5, 4},
                                                                         {1, 2, 3, 4, 5, 6}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 7x7 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{24, 37, 55, 63, 75, 90, 103},
                                                                            {28, 47, 71, 81, 90, 110, 128},
                                                                            {38, 49, 85, 95, 99, 122, 143},
                                                                            {33, 37, 66, 55, 81, 98, 113},
                                                                            {27, 42, 67, 78, 90, 102, 118},
                                                                            {30, 48, 76, 90, 105, 120, 133},
                                                                            {33, 54, 85, 102, 120, 138, 154}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3, 4},
                                                                        {2, 1, 4, 8, 2, 3, 4},
                                                                        {1, 5, 7, 5, 2, 3, 4},
                                                                        {2, 5, 0, 5, 2, 3, 4},
                                                                        {1, 2, 3, 4, 5, 3, 4},
                                                                        {1, 2, 3, 4, 5, 6, 4},
                                                                        {1, 2, 3, 4, 5, 6, 7}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4, 5},
                                                                         {3, 1, 4, 1, 3, 4, 5},
                                                                         {1, 2, 3, 6, 3, 4, 5},
                                                                         {1, 2, 3, 2, 3, 4, 5},
                                                                         {1, 2, 3, 4, 5, 4, 5},
                                                                         {1, 2, 3, 4, 5, 6, 5},
                                                                         {1, 2, 3, 4, 5, 6, 7}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 8x8 square matrices with one thread")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{29, 47, 70, 83, 100, 120, 138, 154},
                                                                            {33, 57, 86, 101, 115, 140, 163, 184},
                                                                            {43, 59, 100, 115, 124, 152, 178, 202},
                                                                            {38, 47, 81, 75, 106, 128, 148, 166},
                                                                            {32, 52, 82, 98, 115, 132, 153, 172},
                                                                            {35, 58, 91, 110, 130, 150, 168, 190},
                                                                            {38, 64, 100, 122, 145, 168, 189, 208},
                                                                            {41, 70, 109, 134, 160, 186, 210, 232}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3, 4, 5},
                                                                        {2, 1, 4, 8, 2, 3, 4, 5},
                                                                        {1, 5, 7, 5, 2, 3, 4, 5},
                                                                        {2, 5, 0, 5, 2, 3, 4, 5},
                                                                        {1, 2, 3, 4, 5, 3, 4, 5},
                                                                        {1, 2, 3, 4, 5, 6, 4, 5},
                                                                        {1, 2, 3, 4, 5, 6, 7, 5},
                                                                        {1, 2, 3, 4, 5, 6, 7, 8}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4, 5, 6},
                                                                         {3, 1, 4, 1, 3, 4, 5, 6},
                                                                         {1, 2, 3, 6, 3, 4, 5, 6},
                                                                         {1, 2, 3, 2, 3, 4, 5, 6},
                                                                         {1, 2, 3, 4, 5, 4, 5, 6},
                                                                         {1, 2, 3, 4, 5, 6, 5, 6},
                                                                         {1, 2, 3, 4, 5, 6, 7, 6},
                                                                         {1, 2, 3, 4, 5, 6, 7, 8}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 2x2 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{9, 7},
                                                                            {7, 5}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1},
                                                                        {2, 1}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2},
                                                                         {3, 1}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 3x3 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{11, 11, 16},
                                                                            {11, 13, 20},
                                                                            {24, 21, 43}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2},
                                                                        {2, 1, 4},
                                                                        {1, 5, 7}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2},
                                                                         {3, 1, 4},
                                                                         {1, 2, 3}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 4x4 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{15, 19, 28, 27	},
	                                                                        {19, 29, 44, 45	},
	                                                                        {29, 31, 58, 59	},
	                                                                        {24, 19, 39, 19	}}));
                    

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4},
                                                                        {2, 1, 4, 8},
                                                                        {1, 5, 7, 5},
                                                                        {2, 5, 0, 5}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2},
                                                                         {3, 1, 4, 1},
                                                                         {1, 2, 3, 6},
                                                                         {1, 2, 3, 2}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 5x5 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{17, 23, 34, 35, 40},
                                                                            {21, 33, 50, 53, 55},
                                                                            {31, 35, 64, 67, 64},
                                                                            {26, 23, 45, 27, 46},
                                                                            {20, 28, 46, 50, 55}}));
        
                    

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2},
                                                                        {2, 1, 4, 8, 2},
                                                                        {1, 5, 7, 5, 2},
                                                                        {2, 5, 0, 5, 2},
                                                                        {1, 2, 3, 4, 5}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3},
                                                                         {3, 1, 4, 1, 3},
                                                                         {1, 2, 3, 6, 3},
                                                                         {1, 2, 3, 2, 3},
                                                                         {1, 2, 3, 4, 5}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 6x6 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{20, 29, 43, 47, 55, 66},
                                                                            {24, 39, 59, 65, 70, 86},
                                                                            {34, 41, 73, 79, 79, 98},
                                                                            {29, 29, 54, 39, 61, 74},
                                                                            {23, 34, 55, 62, 70, 78},
                                                                            {26, 40, 64, 74, 85, 96}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3},
                                                                        {2, 1, 4, 8, 2, 3},
                                                                        {1, 5, 7, 5, 2, 3},
                                                                        {2, 5, 0, 5, 2, 3},
                                                                        {1, 2, 3, 4, 5, 3},
                                                                        {1, 2, 3, 4, 5, 6}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4},
                                                                         {3, 1, 4, 1, 3, 4},
                                                                         {1, 2, 3, 6, 3, 4},
                                                                         {1, 2, 3, 2, 3, 4},
                                                                         {1, 2, 3, 4, 5, 4},
                                                                         {1, 2, 3, 4, 5, 6}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 7x7 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{24, 37, 55, 63, 75, 90, 103},
                                                                            {28, 47, 71, 81, 90, 110, 128},
                                                                            {38, 49, 85, 95, 99, 122, 143},
                                                                            {33, 37, 66, 55, 81, 98, 113},
                                                                            {27, 42, 67, 78, 90, 102, 118},
                                                                            {30, 48, 76, 90, 105, 120, 133},
                                                                            {33, 54, 85, 102, 120, 138, 154}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3, 4},
                                                                        {2, 1, 4, 8, 2, 3, 4},
                                                                        {1, 5, 7, 5, 2, 3, 4},
                                                                        {2, 5, 0, 5, 2, 3, 4},
                                                                        {1, 2, 3, 4, 5, 3, 4},
                                                                        {1, 2, 3, 4, 5, 6, 4},
                                                                        {1, 2, 3, 4, 5, 6, 7}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4, 5},
                                                                         {3, 1, 4, 1, 3, 4, 5},
                                                                         {1, 2, 3, 6, 3, 4, 5},
                                                                         {1, 2, 3, 2, 3, 4, 5},
                                                                         {1, 2, 3, 4, 5, 4, 5},
                                                                         {1, 2, 3, 4, 5, 6, 5},
                                                                         {1, 2, 3, 4, 5, 6, 7}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done

    It("Multiplies two 8x8 square matrices with two threads")
    {
        auto expected = std::shared_ptr<matrix<double>>(new matrix<double>({{29, 47, 70, 83, 100, 120, 138, 154},
                                                                            {33, 57, 86, 101, 115, 140, 163, 184},
                                                                            {43, 59, 100, 115, 124, 152, 178, 202},
                                                                            {38, 47, 81, 75, 106, 128, 148, 166},
                                                                            {32, 52, 82, 98, 115, 132, 153, 172},
                                                                            {35, 58, 91, 110, 130, 150, 168, 190},
                                                                            {38, 64, 100, 122, 145, 168, 189, 208},
                                                                            {41, 70, 109, 134, 160, 186, 210, 232}}));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>({{3, 1, 2, 4, 2, 3, 4, 5},
                                                                        {2, 1, 4, 8, 2, 3, 4, 5},
                                                                        {1, 5, 7, 5, 2, 3, 4, 5},
                                                                        {2, 5, 0, 5, 2, 3, 4, 5},
                                                                        {1, 2, 3, 4, 5, 3, 4, 5},
                                                                        {1, 2, 3, 4, 5, 6, 4, 5},
                                                                        {1, 2, 3, 4, 5, 6, 7, 5},
                                                                        {1, 2, 3, 4, 5, 6, 7, 8}}));

        auto right = std::shared_ptr<matrix<double>>(new matrix<double>({{2, 2, 2, 2, 3, 4, 5, 6},
                                                                         {3, 1, 4, 1, 3, 4, 5, 6},
                                                                         {1, 2, 3, 6, 3, 4, 5, 6},
                                                                         {1, 2, 3, 2, 3, 4, 5, 6},
                                                                         {1, 2, 3, 4, 5, 4, 5, 6},
                                                                         {1, 2, 3, 4, 5, 6, 5, 6},
                                                                         {1, 2, 3, 4, 5, 6, 7, 6},
                                                                         {1, 2, 3, 4, 5, 6, 7, 8}}));

        multiply multiply_command;

        std::shared_ptr<const matrix<double>> result = multiply_command.call(left, right, 1);

        AssertElementsEqual(*expected, *result);
    } Done
}
