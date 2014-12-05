#include <ctime>
#include "../include/project_manager.h"
#include "../include/add.h"
#include "../include/subtract.h"
#include "../include/multiply.h"
#include "../include/random.h"
#include "../include/transpose.h"
#include "../include/random_symmetric.h"
#include "../include/identity.h"
#include "../include/jacobi_eigen_solver.h"

using namespace osoasso;

project_manager::project_manager() 
   : commands_(8,
               { std::make_pair("add", std::shared_ptr<command_with_two_arguments>(new add)),
                 std::make_pair("subtract", std::shared_ptr<command_with_two_arguments>(new subtract)),
                 std::make_pair("multiply", std::shared_ptr<command_with_two_arguments>(new multiply)),
                 std::make_pair("random", std::shared_ptr<command_with_two_arguments>(new random)),
                 std::make_pair("transpose", std::shared_ptr<command_with_one_argument>(new transpose)),
                 std::make_pair("random_symmetric", std::shared_ptr<command_with_one_argument>(new random_symmetric)),
                 std::make_pair("identity", std::shared_ptr<command_with_one_argument>(new identity)),
                 std::make_pair("jacobi_eigen_solver", std::shared_ptr<command_with_one_argument>(new jacobi_eigen_solver)) }),
     matrices_(),
     commits_(),
     commit_tree_()
{
}

expected<commit_data> project_manager::input(const std::string& action, const std::string& user)
{
    time_t commit_time = time(NULL);

    command_dispatcher dispatcher(commands_, matrices_, tags_);
    auto expected_command_data = dispatcher.input(action);
    if (!expected_command_data.has_value())
    {
        return expected<commit_data>::from_string(expected_command_data.get_exception_message());
    }
    auto command_data = expected_command_data.get_value();

    commit_factory factory(commits_, commit_tree_);
    factory.create(action, user, commit_time, command_data.inputs, command_data.output);

    return expected<commit_data>(this->get_last_commit(command_data.tag, command_data.command_duration_seconds));
}

std::shared_ptr<const matrix<double>> project_manager::get_matrix(const std::string& name) const
{
    return matrices_.get(name);
}

std::vector<std::string> project_manager::get_command_names() const
{
    return commands_.get_names();

}

std::vector<std::pair<std::string, std::string>> project_manager::get_command_help() const
{
    std::vector<std::string> command_names = commands_.get_names();
    std::vector<std::pair<std::string, std::string>> command_help;

    for (auto name = command_names.begin(); name != command_names.end(); ++name)
    {
        command_help.push_back(std::make_pair(*name, commands_.get(*name)->get_help()));
    }

    return command_help;
}

commit_data project_manager::get_last_commit(std::string& tag, double command_duration_seconds) const
{
    std::string head_commit_name = commit_tree_.head();
    std::shared_ptr<const commit> head_commit = commits_.get(head_commit_name);

    commit_data data;
    data.action = head_commit->action();
    data.user = head_commit->user();
    data.time = head_commit->time();
    data.output = head_commit->output();
    data.name = head_commit->name();
    data.tag = tag;
    data.command_duration_seconds = command_duration_seconds;

    return data;
}

