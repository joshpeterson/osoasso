#ifndef __ADD_H
#define __ADD_H

#include "matrix.h"

namespace osoasso
{

class add
{
public:
    matrix<double> call(const matrix<double>& left, const matrix<double>& right) const;
};

}

#endif // __ADD_H
