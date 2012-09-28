#ifndef __JACOBI_EIGEN_SOLVER_H
#define __JACOBI_EIGEN_SOLVER_H

#include <memory>
#include <string>
#include "matrix.h"
#include "command_with_one_argument.h"

namespace osoasso
{

class jacobi_eigen_solver : public command_with_one_argument
{
public:
    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> input, int number_of_threads) const;
    std::string get_help() const;
};

}

#endif //JACOBI_EIGEN_SOLVER_H
