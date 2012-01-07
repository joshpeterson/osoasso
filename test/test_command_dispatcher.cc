#include <stdexcept>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include "../test_harness/test.h"
#include "../include/command.h"
#include "../include/command_factory.h"
#include "../include/command_dispatcher.h"
#include "../include/object_repository.h"
#include "../include/matrix_blobber.h"

using namespace osoasso;

class mock_dispatcher_command : public command
{
public:
    mock_dispatcher_command() : command_called_(false)
    {
    }

    std::shared_ptr<const matrix<double>> call(std::shared_ptr<const matrix<double>> left,
                                               std::shared_ptr<const matrix<double>> right) const
    {
        command_called_ = true;
        left_ = left;
        right_ = right;
        auto test = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));
        return test;
    }

    int number_of_arguments() const
    {
        return 2;
    }

    bool command_called() const
    {
        return command_called_;
    }

    std::shared_ptr<const matrix<double>>left_argument() const
    {
        return left_;
    }

    std::shared_ptr<const matrix<double>> right_argument() const
    {
        return right_;
    }


private:
    mutable bool command_called_;
    mutable std::shared_ptr<const matrix<double>> left_;
    mutable std::shared_ptr<const matrix<double>> right_;
};

Define(CommandDispatcher)
{
    It("Accepts an input string and calls the correct command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertTrue(test_command->command_called());
    } Done

    It("Throws an exception when it sees the wrong number of arguments")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);

        std::string exception_message;
        bool exception_thrown = false;
        try
        {
            dispatcher.input("foo([[1 2]], [[3 5]], [[2 6]])");
        }
        catch (const std::runtime_error& e)
        {
            exception_thrown = true;
            exception_message = e.what();
        }

        AssertTrue(exception_thrown);
        AssertEqual(std::string("Command foo expected 2 arguments but 3 arugments were provided: [[1 2]], [[3 5]], [[2 6]]"), exception_message);
    } Done

    It("Throws an exception with the correct wording when it sees the wrong number of arguments with 1 provided")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);

        std::string exception_message;
        bool exception_thrown = false;
        try
        {
            dispatcher.input("foo([[1 2]])");
        }
        catch (const std::runtime_error& e)
        {
            exception_thrown = true;
            exception_message = e.what();
        }

        AssertTrue(exception_thrown);
        AssertEqual(std::string("Command foo expected 2 arguments but 1 argument was provided: [[1 2]]"), exception_message);
    } Done

    It("Passes the correct arguments to the command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        matrix<double> expected_left = {{ 1, 2 }};
        matrix<double> expected_right = {{ 3, 5 }};

        AssertElementsEqual(expected_left, *test_command->left_argument());
        AssertElementsEqual(expected_right, *test_command->right_argument());
    } Done

    It("Stores the arguments to the command in the object repository")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        auto expected_left = std::shared_ptr<const matrix<double>>(new matrix<double>({{ 1, 2 }}));
        auto expected_right = std::shared_ptr<const matrix<double>>(new matrix<double>({{ 3, 5 }}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(expected_left);
        std::shared_ptr<const blob<double>> blob_right = blobber.make_blob(expected_right);

        AssertElementsEqual(*expected_left, *matrices.get(blob_left->name()));
        AssertElementsEqual(*expected_right, *matrices.get(blob_right->name()));
    } Done

    It("Stores the result of the command in the object repository")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        command_dispatcher dispatcher(commands, matrices);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        auto expected_result = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_result = blobber.make_blob(expected_result);

        AssertElementsEqual(*expected_result, *matrices.get(blob_result->name()));
    } Done

    It("Returns the name of the result matrix as the first part of a pair")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        auto expected_result = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_result = blobber.make_blob(expected_result);

        command_dispatcher dispatcher(commands, matrices);
        std::pair<std::string, std::vector<std::string>> result = dispatcher.input("foo([[1 2]], [[3 5]])");
        AssertEqual(blob_result->name(), result.first);

    } Done

    It("Returns the name of the input matrices as the second part of a pair")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;

        auto left = std::shared_ptr<const matrix<double>>(new matrix<double>({{1, 2}}));
        auto right = std::shared_ptr<const matrix<double>>(new matrix<double>({{3, 5}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(left);
        std::shared_ptr<const blob<double>> blob_right = blobber.make_blob(right);

        command_dispatcher dispatcher(commands, matrices);
        std::pair<std::string, std::vector<std::string>> result = dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertEqual(blob_left->name(), result.second[0]);
        AssertEqual(blob_right->name(), result.second[1]);

    } Done

    It("Finds an input by name in the object repository")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        auto expected_left = std::shared_ptr<const matrix<double>>(new matrix<double>({{ 1, 2 }}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(expected_left);

        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        matrices.add(std::make_pair(blob_left->name(), expected_left));

        std::stringstream input;
        input << "foo(" << blob_left->name() << ", [[3 5]])";

        command_dispatcher dispatcher(commands, matrices);
        dispatcher.input(input.str());

        AssertElementsEqual(*expected_left, *matrices.get(blob_left->name()));
    } Done
}
