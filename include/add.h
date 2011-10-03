#ifndef __ADD_H
#define __ADD_H

#include <memory>
#include "matrix.h"
#include "command.h"

namespace osoasso
{

class add : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const;
    int number_of_arguments() const;
};

}

#endif // __ADD_H
