#include <ctime>
#include "../include/commit.h"

using namespace osoasso;

commit::commit(std::string contents, std::string committer, time_t time) : time_(time)
{
}

std::string commit::action() const
{
    return "foo";
}

std::string commit::user() const
{
    return "me";
}

std::string commit::time() const
{
    tm* time_info = gmtime(&time_);
    std::string time(asctime(time_info));

    // Strip off the trailing newline character.
    return time.substr(0, time.size()-1) + " GMT";
}
