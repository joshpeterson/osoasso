#include <random>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include "../include/identity.h"

using namespace osoasso;

std::shared_ptr<const matrix<double>> identity::call(std::shared_ptr<const matrix<double>> size, int number_of_threads) const
{
    if (size->rows() != 1 && size->columns() != 1)
    {
        std::stringstream message;
        message << "The size argument must have one element, but it is of size " << size->rows()
                << "x" << size->columns();
        throw std::invalid_argument(message.str());
    }

    size_t num_rows = (*size)(1,1);

    auto result = std::make_shared<matrix<double>>(num_rows, num_rows);
    for (size_t i = 1; i <= num_rows; ++i)
    {
        for (size_t j = 1; j <= i; ++j)
        {
            if (i != j)
                (*result)(i,j) = 0.0;
            else
                (*result)(i,j) = 1.0;
        }
    }

    return result;
}

std::string identity::get_help() const
{
    return "identity(n) generates the identity matrix of size n x n.";
}

std::shared_ptr<const matrix<double>> identity::operator()(int size) const
{
    auto size_matrix = std::shared_ptr<matrix<double>>(new matrix<double>({{static_cast<double>(size)}}));
    return call(size_matrix, 1);
}
