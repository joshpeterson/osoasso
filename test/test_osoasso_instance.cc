#include "../test_harness/test.h"
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"

using namespace osoasso;

class mock_project_manager : public project_manager
{
public:
    mock_project_manager() : input_called_(false), get_matrix_called_(false), action_(), user_(), name_()
    {
    }

    commit_data input(const std::string& action, const std::string& user)
    {
        input_called_ = true;
        action_ = action;
        user_ = user;

        commit_data data;
        data.action = action;
        data.user = user;
        data.name = "CommitName";
        data.time = "Some time GMT";
        data.output = "OutputName";

        return data;
    }

    std::shared_ptr<const matrix<double>> get_matrix(const std::string& name) const
    {
        get_matrix_called_ = true;
        name_ = name;

        return std::shared_ptr<const matrix<double>>(new matrix<double>({{1, 2}}));
    }
    
    bool input_called() const
    {
        return input_called_;
    }

    bool get_matrix_called() const
    {
        return get_matrix_called_;
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
    mutable bool get_matrix_called_;
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

        message_output output = instance.handle_message(
                                        std::string(input_method_id) + ":foo([[1 5]], [[1 3]]):me@bar.com");

        AssertEqual(message_output_string, output.type);
        AssertEqual(std::string("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName"), output.value.commit_string);
    } Done

    It("Calls the project manager get matrix method")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        instance.handle_message(std::string(get_matrix_method_id) + ":foosha1");

        AssertTrue(manager.get_matrix_called());
    } Done

    It("Calls the project manager get matrix method with the correct name")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

         message_output value = instance.handle_message(std::string(get_matrix_method_id) + ":foosha1");

        AssertEqual("foosha1", manager.name());
    } Done

    It("Returns a double when get matrix is called")
    {
        mock_project_manager manager;
        osoasso_instance instance(manager);

        message_output output = instance.handle_message(std::string(get_matrix_method_id) + ":foosha1");

        AssertEqual(message_output_double, output.type);
        AssertEqual(1.0, output.value.matrix_value);
    } Done

}
