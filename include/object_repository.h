#ifndef __OBJECT_REPOSITORY_H
#define __OBJECT_REPOSITORY_H

#include <memory>
#include <unordered_map>
#include <utility>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace osoasso
{

template <typename RepositoryValueType>
class object_repository
{
public:
    object_repository<RepositoryValueType>()
    {
    }

    object_repository<RepositoryValueType>(int number_of_entries, std::initializer_list<std::pair<std::string, RepositoryValueType>> list)
    {
        // Something is wrong with gcc 4.4.3 which causes this loop to iterate past the end of the std::initializer_list
        // on 64-bit only. To mitigate the problem, I've had to explicitly pass the expected size of the list.
        int iterations = 0;
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            this->add(*i);
            ++iterations;
            if (iterations == number_of_entries)
                break;
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

    std::vector<std::string> get_keys() const
    {
        std::vector<std::string> keys;
        for(auto i = objects_.begin(); i != objects_.end(); ++i)
        {
            keys.push_back(i->first);
        }

        return keys;
    }

    std::vector<RepositoryValueType> get_values() const
    {
        std::vector<RepositoryValueType> values;
        for(auto i = objects_.begin(); i != objects_.end(); ++i)
        {
            values.push_back(i->second);
        }

        return values;
    }

private:
    std::unordered_map<std::string, RepositoryValueType> objects_;
};

}

#endif //__OBJECT_REPOSITORY_H
