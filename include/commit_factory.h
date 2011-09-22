#ifndef __COMMIT_FACTORY_H
#define __COMMIT_FACTORY_H

#include <string>
#include <vector>
#include "commit.h"

namespace osoasso
{

class commit_factory
{
public:
    osoasso::commit create(const std::string& action, const std::string& user, time_t time,
                           const std::vector<std::string>& inputs, const std::string& output) const;
};

}

#endif // __COMMIT_FACTORY_H
