#include <utility>
#include <memory>
#include "../include/commit_factory.h"

using namespace osoasso;

commit_factory::commit_factory(object_repository<std::shared_ptr<const commit>>& commits,
                               tree<std::string>& commit_tree) : commits_(commits), commit_tree_(commit_tree)
{
}

commit commit_factory::create(const std::string& action, const std::string& user, time_t time,
                              const std::vector<std::string>& inputs, const std::string& output)
{
    std::shared_ptr<const commit> new_commit = std::shared_ptr<const commit>(new commit(action, user, time,
                                                                                        inputs, output));
    std::string new_commit_name = new_commit->make_blob().name();
    commits_.add(std::make_pair(new_commit_name, new_commit));
    commit_tree_.insert(new_commit_name);

    return *new_commit;
}
