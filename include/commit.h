#ifndef __COMMIT_H
#define __COMMIT_H

#include <string>
#include <vector>
#include <ostream>
#include "../include/blob.h"

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
    std::string name() const;

    blob<char> make_blob() const;

private:
    std::string action_;
    std::string user_;
    time_t time_;
    std::vector<std::string> inputs_;
    std::string output_;

    void serialize_string(std::ostream& stream, std::string value) const;
};

}

#endif // __COMMIT_H
