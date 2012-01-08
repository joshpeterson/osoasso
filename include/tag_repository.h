#ifndef __TAG_REPOSITORY_H
#define __TAG_REPOSITORY_H

#include <string>
#include <map>

namespace osoasso
{

class tag_repository
{
public:
    void add(std::string tag, std::string object_name);
    std::string get(std::string tag) const;

private:
    std::map<std::string, std::string> tags_;
};

}

#endif // __TAG_REPOSITORY_H
