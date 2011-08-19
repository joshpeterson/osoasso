#ifndef __COMMAND_H
#define __COMMAND_H

#include "matrix.h"

namespace osoasso
{

class command
{
public:
    virtual matrix<double> call(const matrix<double>& left, const matrix<double>& right) const = 0;
    virtual int number_of_arguments() const = 0;
};

}

#endif // __COMMAND_H
