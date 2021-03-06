#ifndef __OSOASSO_INSTANCE_H
#define __OSOASSO_INSTANCE_H

#include <memory>
#include <string>
#include "project_manager.h"
#include "matrix.h"
#include "help_manager.h"

namespace osoasso
{

const char* const input_method_id = "input";

class osoasso_instance
{
public:
    osoasso_instance(project_manager& manager);
    std::string handle_message(const std::string& method_id);
    std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const;

private:
    project_manager& manager_;
    help_manager help_;
};

}

#endif // __OSOASSO_INSTANCE_H
