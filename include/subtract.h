#ifndef __SUBTRACT_H
#define __SUBTRACT_H

#include "matrix.h"

namespace osoasso
{

class subtract
{
public:
    matrix<double> call(const matrix<double>& left, const matrix<double>& right) const;
    int number_of_arguments() const;
};

}

#endif // __SUBTRACT_H
