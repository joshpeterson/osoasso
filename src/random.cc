#include <random>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include "../include/random.h"

using namespace osoasso;

std::shared_ptr<const matrix<double>> random::call(std::shared_ptr<const matrix<double>> rows,
                                                std::shared_ptr<const matrix<double>> columns) const
{
    if (rows->rows() != 1 && rows->columns() != 1)
    {
        std::stringstream message;
        message << "The first argument must have one element, but it is of size " << rows->rows()
                << "x" << rows->columns();
        throw std::invalid_argument(message.str());
    }

    if (columns->rows() != 1 && columns->columns() != 1)
    {
        std::stringstream message;
        message << "The second argument must have one element, but it is of size " << columns->rows()
                << "x" << columns->columns();
        throw std::invalid_argument(message.str());
    }

    size_t num_rows = (*rows)(1,1);
    size_t num_columns = (*columns)(1,1);

    srand(time(NULL));
    auto result = std::shared_ptr<matrix<double>>(new matrix<double>(num_rows, num_columns));
    for (size_t i = 1; i <= num_rows; ++i)
    {
        for (size_t j = 1; j <= num_columns; ++j)
        {
            (*result)(i,j) = rand();
        }
    }

    return result;
}

int random::number_of_arguments() const
{
    return 2;
}
