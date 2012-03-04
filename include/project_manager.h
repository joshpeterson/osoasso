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
#include "tag_repository.h"

namespace osoasso
{

struct commit_data
{
    commit_data() : command_duration_seconds(0.0)
    {
    }

    commit_data(commit_data&& other) : action(std::move(other.action)), user(std::move(other.user)),
        time(std::move(other.time)), output(std::move(other.output)), name(std::move(other.name)),
        tag(std::move(other.tag)), command_duration_seconds(std::move(other.command_duration_seconds))
    {
    }

    std::string action;
    std::string user;
    std::string time;
    std::string output;
    std::string name;
    std::string tag;
    double command_duration_seconds;
};

class project_manager
{
public:
    project_manager();
    virtual ~project_manager() {}
    virtual commit_data input(const std::string& action, const std::string& user);
    virtual std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const;

private:
    command_factory commands_;
    object_repository<std::shared_ptr<const matrix<double>>> matrices_;
    object_repository<std::shared_ptr<const commit>> commits_;
    tag_repository tags_;
    tree<std::string> commit_tree_;

    commit_data get_last_commit(std::string& tag, double command_time) const;
};

}

#endif // __PROJECT_MANAGER_H
