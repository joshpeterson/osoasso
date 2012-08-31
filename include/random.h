#ifndef __RANDOM_H
#define __RANDOM_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_two_arguments.h"

namespace osoasso
{

class random : public command_with_two_arguments
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> rows, std::shared_ptr<const matrix<double>> columns,
                                               int number_of_threads) const;
    std::string get_help() const;
};

}

#endif //RANDOM
