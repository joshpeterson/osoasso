#ifndef __ADD_H
#define __ADD_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_two_arguments.h"

namespace osoasso
{

class add : public command_with_two_arguments
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left, std::shared_ptr<const matrix<double>> right,
                                               int number_of_threads) const;
    std::string get_help() const;
};

}

#endif // __ADD_H
