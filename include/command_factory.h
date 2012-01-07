#ifndef __COMMAND_FACTORY_H
#define __COMMAND_FACTORY_H

#include <utility>
#include <memory>
#include <string>
#include "command.h"
#include "object_repository.h"

namespace osoasso
{

class command_factory
{
public:
    command_factory(std::initializer_list<std::pair<std::string, std::shared_ptr<command>>> commands);
    std::shared_ptr<command> get(std::string name) const;

private:
    object_repository<std::shared_ptr<command>> commands_;
};

}

#endif // __COMMAND_FACTORY_H
