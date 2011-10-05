#ifndef __PROJECT_MANAGER_H
#define __PROJECT_MANAGER_H

#include <memory>
#include <string>
#include "object_repository.h"
#include "matrix.h"
#include "command.h"
#include "command_dispatcher.h"
#include "tree.h"
#include "commit_factory.h"

namespace osoasso
{

struct commit_data
{
    std::string action;
    std::string user;
    std::string time;
    std::string output;
    std::string name;
};

class project_manager
{
public:
    project_manager();
    void input(const std::string& action, const std::string& user);
    commit_data get_last_commit() const;

private:
    command_factory commands_;
    object_repository<std::shared_ptr<const matrix<double>>> matrices_;
    object_repository<std::shared_ptr<const commit>> commits_;
    tree<std::string> commit_tree_;
};

}

#endif // __PROJECT_MANAGER_H
