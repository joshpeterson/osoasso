#include <memory>
#include <random>
#include "../test_harness/test.h"
#include "../test/timer.h"
#include "../include/matrix.h"
#include "../include/multiply.h"

using namespace osoasso;

Define(StressTestMultiply)
{
    It("Multiplies two 1024x1024 matrices")
    {
        srand(time(NULL));

        auto left = std::shared_ptr<matrix<double>>(new matrix<double>(1024, 1024));
        auto right = std::shared_ptr<matrix<double>>(new matrix<double>(1024, 1024));

        for (size_t row = 1; row <= 1024;  ++row)
        {
            for (size_t column = 1; column <= 1024; ++column)
            {
                (*left)(row, column) = rand();
                (*right)(row, column) = rand();
            }
        }

        multiply multiply_command;

        timer multiply_timer;

        multiply_command.call(left, right);

        std::cout << " Time to multiply: " << multiply_timer.elapsed() << "s" << std::endl;
    } Done
}
