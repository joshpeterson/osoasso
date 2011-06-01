#ifndef __COMMIT_H
#define __COMMIT_H

#include <string>

namespace osoasso
{

class commit
{
public:
    commit(std::string contents, std::string committer, time_t time);

    std::string action() const;
    std::string user() const;
    std::string time() const;

private:
    time_t time_;
};

}

#endif // __COMMIT_H
