#ifndef __COMMIT_H
#define __COMMIT_H

#include <string>
#include <vector>

namespace osoasso
{

class commit
{
public:
    commit(std::string action, std::string user_, time_t time, const std::vector<std::string>& inputs, std::string output);

    std::string action() const;
    std::string user() const;
    std::string time() const;
    std::vector<std::string> inputs() const;
    std::string output() const;

private:
    std::string action_;
    std::string user_;
    time_t time_;
    std::vector<std::string> inputs_;
    std::string output_;
};

}

#endif // __COMMIT_H
