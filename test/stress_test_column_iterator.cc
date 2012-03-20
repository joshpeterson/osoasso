#include <memory>
#include <random>
#include <iostream>
#include "../test_harness/test.h"
#include "../include/timer.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(StressTestColumnIterator)
{
    It("Iterates a 1024x1024 matrix by column")
    {
        srand(time(NULL));

        auto big = std::make_shared<matrix<double>>(1024, 1024);

        for (size_t row = 1; row <= 1024;  ++row)
        {
            for (size_t column = 1; column <= 1024; ++column)
            {
                (*big)(row, column) = rand();
            }
        }

        timer column_iteration_timer;

        double value = 0.0;
        for (auto it = big->column_begin(); it != big->column_end(); ++it)
        {
            // Do something so the compiler actually generates the loop.
            value += (*it)[0];
        }

        std::cout << " Time to iterate columns: " << column_iteration_timer.elapsed() << "s" << std::endl;
    } Done
}
