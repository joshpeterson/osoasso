#include "../include/commit_factory.h"

using namespace osoasso;

commit commit_factory::create(const std::string& action, const std::string& user, time_t time,
                              const std::vector<std::string>& inputs, const std::string& output) const
{
    return commit(action, user, time, inputs, output);
}
