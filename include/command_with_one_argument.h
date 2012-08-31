#ifndef __COMMAND_WITH_ONE_ARGUMENT_H
#define __COMMAND_WITH_ONE_ARGUMENT_H

#include <memory>
#include "command.h"
#include "matrix.h"

namespace osoasso
{

class command_with_one_argument : public command
{
public:
    virtual std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> input, int number_of_threads) const = 0;

    virtual int number_of_arguments() const
    {
        return 1;
    }

    virtual std::string get_help() const = 0;
};

}

#endif // __COMMAND_WITH_ONE_ARGUMENT_H
