#ifndef __SUBTRACT_H
#define __SUBTRACT_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_two_arguments.h"

namespace osoasso
{

class subtract : public command_with_two_arguments
{
public:
    expected_const_matrix call(std::shared_ptr<const matrix<double>> left, std::shared_ptr<const matrix<double>> right,
                               int number_of_threads) const;
    std::string get_help() const;
};

}

#endif // __SUBTRACT_H
