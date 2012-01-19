#ifndef __RANDOM_H
#define __RANDOM_H

#include <memory>
#include "matrix.h"
#include "command.h"

namespace osoasso
{

class random : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> rows,
                                               std::shared_ptr<const matrix<double>> columns) const;
    int number_of_arguments() const;
};

}

#endif //RANDOM
