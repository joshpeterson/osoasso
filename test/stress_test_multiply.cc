#include <memory>
#include <random>
#include <iostream>
#include "../test_harness/test.h"
#include "../include/timer.h"
#include "../include/matrix.h"
#include "../include/multiply.h"

using namespace osoasso;

Define(StressTestMultiply)
{
    It("Multiplies two 1024x1024 matrices")
    {
        srand(time(NULL));

        auto left = std::make_shared<matrix<double>>(1024, 1024);
        auto right = std::make_shared<matrix<double>>(1024, 1024);

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

        multiply_command.call(left, right, 2);

        std::cout << " Time to multiply: " << multiply_timer.elapsed() << "s" << std::endl;
    } Done
}
