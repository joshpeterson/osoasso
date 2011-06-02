#ifndef __COMMIT_H
#define __COMMIT_H

#include <string>

namespace osoasso
{

class commit
{
public:
    commit(std::string action, std::string user_, time_t time);

    std::string action() const;
    std::string user() const;
    std::string time() const;

private:
    std::string action_;
    std::string user_;
    time_t time_;
};

}

#endif // __COMMIT_H
