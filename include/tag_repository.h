#ifndef __TAG_REPOSITORY_H
#define __TAG_REPOSITORY_H

#include <string>

namespace osoasso
{

class tag_repository
{
public:
    void add(std::string tag, std::string object_name);
    std::string get(std::string tag);
};

}

#endif // __TAG_REPOSITORY_H
