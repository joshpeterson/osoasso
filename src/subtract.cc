#include <sstream>
#include <stdexcept>
#include "../include/subtract.h"
#include "../include/matrix.h"

using namespace osoasso;

expected_const_matrix subtract::call(std::shared_ptr<const matrix<double>> left, std::shared_ptr<const matrix<double>> right,
                                     int number_of_threads) const
{
    if (left->rows() != right->rows())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of rows left: " << left->rows()
                << " right: " << right->rows();
        INVALID_ARGUMENT_CONST(std::invalid_argument(message.str()));
    }
    else if (left->columns() != right->columns())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of columns left: " << left->columns() 
                << " right: " << right->columns();
        INVALID_ARGUMENT_CONST(std::invalid_argument(message.str()));
    }

    auto result = std::make_shared<matrix<double>>(left->rows(), left->columns());
    for (size_t i = 1; i <= left->rows(); ++i)
    {
        for (size_t j = 1; j <= left->columns(); ++j)
        {
            (*result)(i,j) = (*left)(i,j) - (*right)(i,j);
        }
    }

    return expected_const_matrix(result);
}

std::string subtract::get_help() const
{
    return "subtract(A,B) computes the difference of two matrices m x n A and B, with A on the left.";
}
