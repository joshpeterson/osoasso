#ifndef __OSOASSO_INSTANCE_H
#define __OSOASSO_INSTANCE_H

#include <memory>
#include <string>
#include "project_manager_itf.h"
#include "matrix.h"

namespace osoasso
{

const char* const input_method_id = "input";
const char* const get_matrix_method_id = "getMatrix";

union message_output
{
    const char* commit_string;
    double matrix_value;
};


class osoasso_instance
{
public:
    osoasso_instance(project_manager_itf& manager);
    message_output handle_message(const std::string& method_id);
    std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const;

private:
    project_manager_itf& manager_;
};

}

#endif // __OSOASSO_INSTANCE_H
