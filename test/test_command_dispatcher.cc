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
#include "../include/tag_repository.h"

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
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertTrue(test_command->command_called());
    } Done

    It("Throws an exception when it sees the wrong number of arguments")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);

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
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);

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
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
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
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
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
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        auto expected_result = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_result = blobber.make_blob(expected_result);

        AssertElementsEqual(*expected_result, *matrices.get(blob_result->name()));
    } Done

    It("Returns the name of the result matrix in a command data struct")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        auto expected_result = std::shared_ptr<const matrix<double>>(new matrix<double>({{1}, {1}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_result = blobber.make_blob(expected_result);

        command_dispatcher dispatcher(commands, matrices, tags);
        command_data result = dispatcher.input("foo([[1 2]], [[3 5]])");
        AssertEqual(blob_result->name(), result.output);

    } Done

    It("Returns the name of the input matrices in a command data struct")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        auto left = std::shared_ptr<const matrix<double>>(new matrix<double>({{1, 2}}));
        auto right = std::shared_ptr<const matrix<double>>(new matrix<double>({{3, 5}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(left);
        std::shared_ptr<const blob<double>> blob_right = blobber.make_blob(right);

        command_dispatcher dispatcher(commands, matrices, tags);
        command_data result = dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertEqual(blob_left->name(), result.inputs[0]);
        AssertEqual(blob_right->name(), result.inputs[1]);

    } Done

    It("Returns the tag in a command data struct")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        command_data result = dispatcher.input("tag = foo([[1 2]], [[3 5]])");
        AssertEqual("tag", result.tag);
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
        tag_repository tags;

        std::stringstream input;
        input << "foo(" << blob_left->name() << ", [[3 5]])";

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input(input.str());

        AssertElementsEqual(*expected_left, *test_command->left_argument());
    } Done

    It("Stores the tag with the correct result name in the tag repository")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("bar = foo([[1 2]], [[3 5]])");

        AssertEqual(std::string("f8febc7d 612c9ce4 53575949 67981bd6 33215355"), tags.get("bar"));
    } Done

    It("Finds an input by tag in the tag repository")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        auto expected_left = std::shared_ptr<const matrix<double>>(new matrix<double>({{ 1, 2 }}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(expected_left);

        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        matrices.add(std::make_pair(blob_left->name(), expected_left));

        tag_repository tags;
        tags.add("tag", blob_left->name());

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo(tag, [[3 5]])");

        AssertElementsEqual(*expected_left, *test_command->left_argument());
    } Done

    It("Does not add a tag if one is not represent in the input")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo([[1 2]], [[3 5]])");

        AssertEqual<size_t>(0, tags.count());
    } Done

    It("Returns the time to execute the command")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };
        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        command_data data = dispatcher.input("foo([[1 2]], [[3 5]])");

        // Verify that we at least get a non-negative time less than 1 second.
        AssertTrue(data.command_duration_seconds >= 0 && data.command_duration_seconds < 1);
    } Done

    It("Creates a new matrix for a single integer input")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        auto expected_left = std::shared_ptr<const matrix<double>>(new matrix<double>({{2}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(expected_left);

        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo(2, [[3 5]])");

        AssertElementsEqual(*expected_left, *test_command->left_argument());
    } Done

    It("Creates a new matrix for a single double input")
    {
        std::shared_ptr<mock_dispatcher_command> test_command = std::make_shared<mock_dispatcher_command>();

        command_factory commands = { std::make_pair("foo", std::shared_ptr<command>(test_command)) };

        auto expected_left = std::shared_ptr<const matrix<double>>(new matrix<double>({{2.3}}));

        matrix_blobber<double> blobber;
        std::shared_ptr<const blob<double>> blob_left = blobber.make_blob(expected_left);

        object_repository<std::shared_ptr<const matrix<double>>> matrices;
        tag_repository tags;

        command_dispatcher dispatcher(commands, matrices, tags);
        dispatcher.input("foo(2.3, [[3 5]])");

        AssertElementsEqual(*expected_left, *test_command->left_argument());
    } Done
}
