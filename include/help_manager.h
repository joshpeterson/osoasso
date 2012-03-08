#ifndef __HELP_MANAGER_H
#define __HELP_MANAGER_H

#include <string>
#include <vector>

namespace osoasso
{

class help_manager
{
public:
    help_manager(const std::vector<std::string>& command_names);
    std::string get_help_for_action(const std::string& action);

private:
    const std::vector<std::string> command_names_;
};

}

#endif // __HELP_MANAGER_H
