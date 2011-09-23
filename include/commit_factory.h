#ifndef __COMMIT_FACTORY_H
#define __COMMIT_FACTORY_H

#include <string>
#include <vector>
#include <memory>
#include "commit.h"
#include "object_repository.h"

namespace osoasso
{

class commit_factory
{
public:
    commit_factory(osoasso::object_repository<std::shared_ptr<const osoasso::commit>>& commits);
    osoasso::commit create(const std::string& action, const std::string& user, time_t time,
                           const std::vector<std::string>& inputs, const std::string& output);

private:
    osoasso::object_repository<std::shared_ptr<const osoasso::commit>>& commits_;
};

}

#endif // __COMMIT_FACTORY_H
