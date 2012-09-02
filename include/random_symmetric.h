#ifndef __RANDOM_SYMMETRIC_H
#define __RANDOM_SYMMETRIC_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_one_argument.h"

namespace osoasso
{

class random_symmetric : public command_with_one_argument
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> size, int number_of_threads) const;
    std::string get_help() const;
};

}

#endif //RANDOM_SYMMETRIC_H
