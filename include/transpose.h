#ifndef __TRANSPOSE_H
#define __TRANSPOSE_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_two_arguments.h"

namespace osoasso
{

class transpose : public command_with_two_arguments
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> input, std::shared_ptr<const matrix<double>> dummy, int number_of_threads) const;
    std::string get_help() const;
};

}

#endif //TRANSPOSE_H
