#ifndef __MULTIPLY_H
#define __MULTIPLY_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command.h"

namespace osoasso
{

class multiply : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const;
    int number_of_arguments() const;
    std::string get_help() const;
};

}

#endif // __MULTIPLY_H
