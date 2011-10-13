#ifndef __PROJECT_MANAGER_ITF_H
#define __PROJECT_MANAGER_ITF_H

#include <string>
#include <memory>
#include "matrix.h"

namespace osoasso
{

struct commit_data
{
    commit_data()
    {
    }

    commit_data(commit_data&& other) : action(std::move(other.action)), user(std::move(other.user)),
        time(std::move(other.time)), output(std::move(other.output)), name(std::move(other.name))
    {
    }

    std::string action;
    std::string user;
    std::string time;
    std::string output;
    std::string name;
};

class project_manager_itf
{
public:
    virtual commit_data input(const std::string& action, const std::string& user) = 0;
    virtual std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const = 0;
};

}

#endif // __PROJECT_MANAGER_ITF_H
