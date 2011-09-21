#include "../include/commit_factory.h"

using namespace osoasso;

commit commit_factory::create(const std::string& action, const std::string& user,
                              const std::vector<std::string>& inputs, const std::string& output) const
{
    return commit(action, user, 0, inputs, output);
}
