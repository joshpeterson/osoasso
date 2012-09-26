#ifndef __IDENTITY_H
#define __IDENTITY_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_one_argument.h"

namespace osoasso
{

class identity : public command_with_one_argument
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> size, int number_of_threads) const;
    std::string get_help() const;

    std::shared_ptr<const matrix<double>> operator()(int size) const;
};

}

#endif //IDENTITY_H
