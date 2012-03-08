#ifndef __HELP_MANAGER_H
#define __HELP_MANAGER_H

#include <string>
#include <vector>
#include <utility>

namespace osoasso
{

class help_manager
{
public:
    help_manager(const std::vector<std::pair<std::string, std::string>>& command_help);
    std::string get_help_for_action(const std::string& action);

private:
    const std::vector<std::pair<std::string, std::string>> command_help_;
};

}

#endif // __HELP_MANAGER_H
