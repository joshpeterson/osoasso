#include <sstream>
#include <stdexcept>
#include "../include/add.h"
#include "../include/matrix.h"

using namespace osoasso;

std::shared_ptr<const matrix<double>> add::call(std::shared_ptr<const matrix<double>> left,
                                                std::shared_ptr<const matrix<double>> right) const
{
    if (left->rows() != right->rows())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of rows left: " << left->rows() 
                << " right: " << right->rows();
        throw std::invalid_argument(message.str());
    }
    else if (left->columns() != right->columns())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of columns left: " << left->columns() 
                << " right: " << right->columns();
        throw std::invalid_argument(message.str());
    }

    auto result = std::make_shared<matrix<double>>(left->rows(), left->columns());
    for (size_t i = 1; i <= left->rows(); ++i)
    {
        for (size_t j = 1; j <= left->columns(); ++j)
        {
            (*result)(i,j) = (*left)(i,j) + (*right)(i,j);
        }
    }

    return result;
}

int add::number_of_arguments() const
{
    return 2;
}

std::string add::get_help() const
{
    return "add(A,B) computes the sum of two matrices m x n A and B.";
}
