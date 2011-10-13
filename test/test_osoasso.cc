#include "../test_harness/test.h"
#include "../include/osoasso.h"
#include "../include/project_manager_itf.h"

using namespace osoasso;

class mock_project_manager : public project_manager_itf
{
public:
    mock_project_manager() : input_called_(false), action_(), user_()
    {
    }

    commit_data input(const std::string& action, const std::string& user)
    {
        input_called_ = true;
        action_ = action;
        user_ = user;

        return commit_data();
    }
    
    bool input_called() const
    {
        return input_called_;
    }

    std::string action() const
    {
        return action_;
    }

    std::string user() const
    {
        return user_;
    }

private:
    bool input_called_;
    std::string action_;
    std::string user_;
};

Define(Osoasso)
{
    It("Calls the project manager input method when an input message occurs")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        instance.handle_message(std::string(input_method_id) + "::");

        AssertTrue(manager.input_called());
    } Done

    It("Calls the project manager input method with the correct action")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        instance.handle_message(std::string(input_method_id) + ":foo([[1 5]], [[1 3]]):");

        AssertEqual("foo([[1 5]], [[1 3]])", manager.action());
    } Done

    It("Calls the project manager input method with the correct user")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        instance.handle_message(std::string(input_method_id) + ":foo([[1 5]], [[1 3]]):me@bar.com");

        AssertEqual("me@bar.com", manager.user());
    } Done
}
