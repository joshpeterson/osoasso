#include <string>
#include "command_factory.h"

namespace osoasso
{

class command_dispatcher
{
public:
    command_dispatcher(const command_factory& commands);
    void input(const std::string& input) const;

private:
    const command_factory& commands_;
};

}
