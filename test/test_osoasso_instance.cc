#include <string>
#include "../test_harness/test.h"
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"
#include "../include/version.h"

using namespace osoasso;

class mock_project_manager : public project_manager
{
public:
    mock_project_manager() : input_called_(false), action_(), user_(), name_()
    {
    }

    commit_data input(const std::string& action, const std::string& user)
    {
        if (action == "error action")
        {
            throw std::runtime_error("Error message");
        }

        input_called_ = true;
        action_ = action;
        user_ = user;

        commit_data data;
        data.action = action;
        data.user = user;
        data.name = "CommitName";
        data.time = "Some time GMT";
        data.output = "OutputName";
        data.command_duration_seconds = 0.469;

        if (action.find("tag") != std::string::npos)
        {
            data.tag = "tag";
        }

        return data;
    }

    std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const
    {
        name_ = name;

        return std::shared_ptr<const matrix<double>>(new matrix<double>({{1, 2}}));
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

    std::string name() const
    {
        return name_;
    }


private:
    bool input_called_;
    std::string action_;
    std::string user_;
    mutable std::string name_;
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

    It("Returns a commit string when input is called")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        std::string output = instance.handle_message(
                                        std::string(input_method_id) + ":foo([[1 5]], [[1 3]]):me@bar.com");

        AssertEqual(std::string("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#0.469#OutputName#<table id=\"matrix\"><tr><td>|</td><td>1</td><td>2</td><td>|</td></tr></table>"), output);
    } Done

    It("Returns an error message when an exception occurs")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        std::string output = instance.handle_message(std::string(input_method_id) + ":error action:me@bar.com");

        AssertEqual(std::string("error#error action#Error message"), output);
    } Done

    It("Returns a commit string without the output when input is called with a tag")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        std::string output = instance.handle_message(
                                        std::string(input_method_id) + ":tag = foo([[1 5]], [[1 3]]):me@bar.com");

        AssertEqual(std::string("CommitName#tag = foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#0.469#OutputName"), output);
    } Done

    It("Returns a time for the command when input is called")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        std::string output = instance.handle_message(
                                        std::string(input_method_id) + ":tag = foo([[1 5]], [[1 3]]):me@bar.com");

        AssertEqual(std::string("CommitName#tag = foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#0.469#OutputName"), output);
    } Done

    It("Calls the help manager when a string starts with help")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        std::stringstream help_message;
        help_message << "text#help#"
                     << "Osoasso Version " << VERSION << "\n"
                     << "For a list of commands, type this: help commands";

        AssertEqual(help_message.str(), instance.handle_message(":help:me@bar.com"));
    } Done
}
