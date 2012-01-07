#ifndef __OBJECT_REPOSITORY_H
#define __OBJECT_REPOSITORY_H

#include <memory>
#include <unordered_map>
#include <utility>
#include <string>
#include <sstream>
#include <stdexcept>

namespace osoasso
{

template <typename RepositoryValueType>
class object_repository
{
public:
    object_repository<RepositoryValueType>()
    {
    }

    object_repository<RepositoryValueType>(std::initializer_list<std::pair<std::string, RepositoryValueType>> list)
    {
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            this->add(*i);
        }
    }

    void add(std::pair<std::string, RepositoryValueType> object)
    {
        objects_.insert(object);
    }

    RepositoryValueType get(const std::string& name) const
    {
        auto found_object = objects_.find(name);
        if (found_object != objects_.end())
        {
            return found_object->second;
        }
        else
        {
            std::stringstream message;
            message << "No object found with name: " << name;
            throw std::domain_error(message.str());
        }
    }

    size_t size() const
    {
        return objects_.size();
    }

private:
    std::unordered_map<std::string, RepositoryValueType> objects_;
};

}

#endif //__OBJECT_REPOSITORY_H
