#include <random>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include "../include/random_symmetric.h"

using namespace osoasso;

expected_const_matrix random_symmetric::call(std::shared_ptr<const matrix<double>> size, int number_of_threads) const
{
    if (size->rows() != 1 && size->columns() != 1)
    {
        std::stringstream message;
        message << "The size argument must have one element, but it is of size " << size->rows()
                << "x" << size->columns();
        INVALID_ARGUMENT_CONST(std::invalid_argument(message.str()));
    }

    size_t num_rows = (*size)(1,1);

    srand(time(NULL));
    auto result = std::make_shared<matrix<double>>(num_rows, num_rows);
    for (size_t i = 1; i <= num_rows; ++i)
    {
        for (size_t j = 1; j <= i; ++j)
        {
            double value = rand();
            (*result)(i,j) = value;
            (*result)(j,i) = value;
        }
    }

    return expected_const_matrix(result);
}

std::string random_symmetric::get_help() const
{
    return "random_symmetric(n) generates a random symmetric matrix of size n x n.";
}
