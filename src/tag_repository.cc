#include <sstream>
#include <stdexcept>
#include "../include/tag_repository.h"

using namespace osoasso;

void tag_repository::add(const std::string& tag, const std::string& object_name)
{
    tags_[tag] = object_name;
}

std::string tag_repository::get(const std::string& tag) const
{
    auto found = tags_.find(tag);
    if (found != tags_.end())
    {
        return found->second;
    }

    std::stringstream message;
    message << "The tag " << tag << " does not exist.";
    throw std::runtime_error(message.str());
}

bool tag_repository::contains(const std::string& tag) const
{
    return tags_.find(tag) != tags_.end();
}
