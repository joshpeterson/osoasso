#include <sstream>
#include <stdexcept>
#include "../include/multiply.h"
#include "../include/matrix.h"

using namespace osoasso;

std::shared_ptr<const matrix<double>> multiply::call(std::shared_ptr<const matrix<double>> left,
                                                     std::shared_ptr<const matrix<double>> right) const
{
    if (left->columns() != right->rows())
    {
        std::stringstream message;
        message << "The number of columns in the left metrix (" << left->columns()
                << ") is not the same as the number of rows in the right matrix ("
                << right->rows() << ").";
        throw std::invalid_argument(message.str());
    }

    auto result = std::make_shared<matrix<double>>(left->rows(), right->columns());
    for (size_t i = 1; i <= left->rows(); ++i)
    {
        for (size_t j = 1; j <= right->columns(); ++j)
        {
            for (size_t k = 1; k <= left->columns(); ++k)
            {
                (*result)(i,j) += (*left)(i,k) * (*right)(k,j);
            }
        }
    }

    return result;
}

int multiply::number_of_arguments() const
{
    return 2;
}
