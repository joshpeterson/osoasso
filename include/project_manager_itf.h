#ifndef __PROJECT_MANAGER_ITF_H
#define __PROJECT_MANAGER_ITF_H

namespace osoasso
{

class project_manager_itf
{
public:
    virtual void input(const std::string& action, const std::string& user) = 0;
};

}

#endif // __PROJECT_MANAGER_ITF_H
