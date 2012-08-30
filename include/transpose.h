#ifndef __TRANSPOSE_H
#define __TRANSPOSE_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command.h"

namespace osoasso
{

class transpose : public command
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> input, std::shared_ptr<const matrix<double>> dummy, int number_of_threads) const;
    int number_of_arguments() const;
    std::string get_help() const;
};

}

#endif //TRANSPOSE_H
