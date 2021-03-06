#ifndef __COMMAND_WITH_TWO_ARGUMENTS_H
#define __COMMAND_WITH_TWO_ARGUMENTS_H

#include <memory>
#include "command.h"
#include "matrix.h"

namespace osoasso
{

class command_with_two_arguments : public command
{
public:
    virtual expected_const_matrix call(std::shared_ptr<const matrix<double>> left, std::shared_ptr<const matrix<double>> right,
                                       int number_of_threads) const = 0;
    virtual int number_of_arguments() const
    {
        return 2;
    }

    virtual std::string get_help() const = 0;
};

}

#endif // __COMMAND_WITH_TWO_ARGUMENTS_H
