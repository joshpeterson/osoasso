#include <utility>
#include <memory>
#include "../include/commit_factory.h"

using namespace osoasso;

commit_factory::commit_factory(object_repository<std::shared_ptr<const commit>>& commits) : commits_(commits)
{
}

commit commit_factory::create(const std::string& action, const std::string& user, time_t time,
                              const std::vector<std::string>& inputs, const std::string& output)
{
    std::shared_ptr<const commit> new_commit = std::shared_ptr<const commit>(new commit(action, user, time,
                                                                                        inputs, output));

    commits_.add(std::make_pair(new_commit->make_blob().name(), new_commit));


    return *new_commit;
}
