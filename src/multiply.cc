#include <sstream>
#include <stdexcept>
#include "../include/multiply.h"
#include "../include/matrix.h"
#include <iostream>

using namespace osoasso;

std::shared_ptr<const matrix<double>> multiply::call(std::shared_ptr<const matrix<double>> left,
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

    auto result = std::shared_ptr<matrix<double>>(new matrix<double>(left->rows(), left->columns()));
    for (size_t i = 1; i <= left->rows(); ++i)
    {
        for (size_t j = 1; j <= left->rows(); ++j)
        {
            for (size_t k = 1; k <= left->rows(); ++k)
            {
                (*result)(i,k) += (*left)(i,j) * (*right)(j,k);
                //std::cout << i << "," << j << "," << k << " " << (*left)(i,j) << " " <<  (*right)(j,k) << " " << (*result)(i,k) << std::endl;
            }
        }
    }

    return result;
}

int multiply::number_of_arguments() const
{
    return 2;
}
