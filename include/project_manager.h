#ifndef __PROJECT_MANAGER_H
#define __PROJECT_MANAGER_H

#include <memory>
#include <string>
#include "project_manager_itf.h"
#include "object_repository.h"
#include "matrix.h"
#include "command.h"
#include "command_dispatcher.h"
#include "tree.h"
#include "commit_factory.h"

namespace osoasso
{

class project_manager : public project_manager_itf
{
public:
    project_manager();
    commit_data input(const std::string& action, const std::string& user);
    std::shared_ptr<const matrix<double>> get_matrix(std::string name) const;

private:
    command_factory commands_;
    object_repository<std::shared_ptr<const matrix<double>>> matrices_;
    object_repository<std::shared_ptr<const commit>> commits_;
    tree<std::string> commit_tree_;

    commit_data get_last_commit() const;
};

}

#endif // __PROJECT_MANAGER_H
