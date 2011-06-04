#include <ctime>
#include <sstream>
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

std::string commit::name() const
{
    return this->make_blob().name();
}

blob<char> commit::make_blob() const
{
    std::stringstream commit_stream;
    this->serialize_string(commit_stream, action_);
    this->serialize_string(commit_stream, user_);
    for (auto i = inputs_.cbegin(); i != inputs_.cend(); ++i)
    {
        this->serialize_string(commit_stream, *i);
    }
    this->serialize_string(commit_stream, output_);
    commit_stream<< time_;

    std::string commit_string = commit_stream.str();
    return blob<char>(commit_string.begin(), commit_string.end());
}

void commit::serialize_string(std::ostream& stream, std::string value) const
{
    stream << value.size() << value;
}
