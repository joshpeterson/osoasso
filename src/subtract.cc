#include <sstream>
#include <stdexcept>
#include "../include/subtract.h"
#include "../include/matrix.h"

using namespace osoasso;

matrix<double> subtract::call(const matrix<double>& left, const matrix<double>& right) const
{
    if (left.rows() != right.rows())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of rows left: " << left.rows() 
                << " right: " << right.rows();
        throw std::invalid_argument(message.str());
    }
    else if (left.columns() != right.columns())
    {
        std::stringstream message;
        message << "Matrices do not have the same number of columns left: " << left.columns() 
                << " right: " << right.columns();
        throw std::invalid_argument(message.str());
    }

    matrix<double> result(left.rows(), left.columns());
    for (size_t i = 1; i <= left.rows(); ++i)
    {
        for (size_t j = 1; j <= left.columns(); ++j)
        {
            result(i,j) = left(i,j) - right(i,j);
        }
    }

    return result;
}

int subtract::number_of_arguments() const
{
    return 2;
}
