#include <string>
#include <vector>
#include <memory>
#include "../test_harness/test.h"
#include "../include/commit_factory.h"
#include "../include/commit.h"
#include "../include/object_repository.h"
#include "../include/tree.h"

using namespace osoasso;

Define(CommitFactory)
{
    It("Accepts an input string and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs;

        commit result = factory.create("x = foo(1)", "", 0, inputs, "");

        AssertEqual("x = foo(1)", result.action());
    } Done

    It("Accepts a user and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs;

        commit result = factory.create("", "me", 0, inputs, "");

        AssertEqual("me", result.user());
    } Done

    It("Accepts a list of inputs and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs = { "input1", "input2", "input3" };

        commit result = factory.create("", "", 0, inputs, "");

        AssertElementsEqual(inputs, result.inputs());
    } Done

    It("Accepts an output and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs;

        commit result = factory.create("", "", 0, inputs, "output");

        AssertEqual("output", result.output());
    } Done

    It("Accepts an output and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs;

        commit result = factory.create("", "", 0, inputs, "output");

        AssertEqual("output", result.output());
    } Done

    It("Accepts a time and creates a commit")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs;

        commit result = factory.create("", "", 1306927186, inputs, "");

        AssertEqual("Wed Jun  1 11:19:46 2011 GMT", result.time());
    } Done

    It("Adds the commit to the commit repository")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs = { "input1", "input2", "input3" };

        commit result = factory.create("foo", "me", 1306927186, inputs, "output");

        std::string expected_commit_name = result.make_blob().name();

        AssertTrue(commits.get(expected_commit_name) != NULL);
    } Done

    It("Adds the commit name to the commit tree")
    {
        object_repository<std::shared_ptr<const commit>> commits;
        tree<std::string> commit_tree;
        commit_factory factory(commits, commit_tree);

        std::vector<std::string> inputs = { "input1", "input2", "input3" };

        commit result = factory.create("foo", "me", 1306927186, inputs, "output");

        std::string expected_commit_name = result.make_blob().name();

        AssertEqual(expected_commit_name, commit_tree.head());
    } Done
}
