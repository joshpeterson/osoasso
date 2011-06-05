#include <memory>
#include <unordered_map>
#include <utility>
#include <string>

namespace osoasso
{

template <typename RepositoryValueType>
class object_repository
{
public:
    void add(std::shared_ptr<RepositoryValueType> object)
    {
        objects_.insert(std::make_pair(object->name(), object));
    }

    std::shared_ptr<RepositoryValueType> get(std::string name)
    {
        auto found_object = objects_.find(name);
        return found_object != objects_.end() ? found_object->second : std::shared_ptr<RepositoryValueType>();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<RepositoryValueType>> objects_;
};

}
