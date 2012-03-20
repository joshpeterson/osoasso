#include <memory>
#include <random>
#include <iostream>
#include "../test_harness/test.h"
#include "../include/timer.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(StressTestRowIterator)
{
    It("Iterates a 1024x1024 matrix by row")
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

        timer row_iteration_timer;

        double value = 0.0;
        for (auto it = big->row_begin(); it != big->row_end(); ++it)
        {
            // Do something so the compiler actually generates the loop.
            value += (*it)[0];
        }

        std::cout << " Time to iterate rows: " << row_iteration_timer.elapsed() << "s" << std::endl;
    } Done
}
