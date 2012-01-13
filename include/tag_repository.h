#ifndef __TAG_REPOSITORY_H
#define __TAG_REPOSITORY_H

#include <string>
#include <map>

namespace osoasso
{

class tag_repository
{
public:
    void add(const std::string& tag, const std::string& object_name);
    std::string get(const std::string& tag) const;
    bool contains(const std::string& tag) const;

private:
    std::map<std::string, std::string> tags_;
};

}

#endif // __TAG_REPOSITORY_H
