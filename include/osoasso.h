#ifndef __OSOASSO_H
#define __OSOASSO_H

#include "project_manager_itf.h"

namespace osoasso
{

const char* const input_method_id = "input";

class osoasso_instance
{
public:
    osoasso_instance(project_manager_itf& manager);
    void handle_message(const std::string& method_id);

private:
    project_manager_itf& manager_;
};

}

#endif // __OSOASSO_H
