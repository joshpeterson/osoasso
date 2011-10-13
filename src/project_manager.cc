#include "../include/project_manager.h"
#include "../include/add.h"
#include "../include/subtract.h"

using namespace osoasso;

project_manager::project_manager() 
   : commands_({ std::make_pair("add", std::shared_ptr<command>(new add)),
                 std::make_pair("subtract", std::shared_ptr<command>(new subtract)) }),
     matrices_(),
     commits_(),
     commit_tree_()
{
}

commit_data project_manager::input(const std::string& action, const std::string& user)
{
    time_t commit_time = time(NULL);

    command_dispatcher dispatcher(commands_, matrices_);
    auto command_data = dispatcher.input(action);

    commit_factory factory(commits_, commit_tree_);
    factory.create(action, user, commit_time, command_data.second, command_data.first);

    return this->get_last_commit();
}

std::shared_ptr<const matrix<double>> project_manager::get_matrix(const std::string& name) const
{
    return matrices_.get(name);
}

commit_data project_manager::get_last_commit() const
{
    std::string head_commit_name = commit_tree_.head();
    std::shared_ptr<const commit> head_commit = commits_.get(head_commit_name);

    commit_data data;
    data.action = head_commit->action();
    data.user = head_commit->user();
    data.time = head_commit->time();
    data.output = head_commit->output();
    data.name = head_commit->name();

    return data;
}

