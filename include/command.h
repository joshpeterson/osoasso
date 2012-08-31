#ifndef __COMMAND_H
#define __COMMAND_H

#include <memory>
#include "matrix.h"

namespace osoasso
{

class command
{
public:
    virtual int number_of_arguments() const = 0;
    virtual std::string get_help() const = 0;
};

}

#endif // __COMMAND_H
