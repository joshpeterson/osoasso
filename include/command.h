#ifndef __COMMAND_H
#define __COMMAND_H

#include <memory>
#include "matrix.h"
#include "expected.h"

namespace osoasso
{

typedef expected<std::shared_ptr<const matrix<double>>> expected_const_matrix;
typedef expected<std::shared_ptr<matrix<double>>> expected_matrix;

#define INVALID_ARGUMENT(e) \
    do { \
    auto __error = std::make_shared<std::invalid_argument>(e); \
    return expected_matrix(__error); \
    } while (0) \
    

#define INVALID_ARGUMENT_CONST(e) \
    do { \
    auto __error = std::make_shared<std::invalid_argument>(e); \
    return expected_const_matrix(__error); \
    } while (0) \

class command
{
public:
    virtual int number_of_arguments() const = 0;
    virtual std::string get_help() const = 0;
};

}

#endif // __COMMAND_H
