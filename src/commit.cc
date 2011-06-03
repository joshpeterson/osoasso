#include <ctime>
#include "../include/commit.h"

using namespace osoasso;

commit::commit(std::string action, std::string user, time_t time, const std::vector<std::string>& inputs, std::string output) : 
    action_(action), user_(user), time_(time), inputs_(inputs), output_(output)
{
}

std::string commit::action() const
{
    return action_;
}

std::string commit::user() const
{
    return user_;
}

std::string commit::time() const
{
    tm* time_info = gmtime(&time_);
    std::string time(asctime(time_info));

    // Strip off the trailing newline character.
    return time.substr(0, time.size()-1) + " GMT";
}

std::vector<std::string> commit::inputs() const
{
    return inputs_;
}

std::string commit::output() const
{
    return output_;
}
