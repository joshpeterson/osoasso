#ifndef __SUBTRACT_H
#define __SUBTRACT_H

#include <memory>
#include "matrix.h"

namespace osoasso
{

class subtract
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const;
    int number_of_arguments() const;
};

}

#endif // __SUBTRACT_H
