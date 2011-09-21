#include <string>
#include <vector>
#include "../test_harness/test.h"
#include "../include/commit_factory.h"
#include "../include/commit.h"

using namespace osoasso;

Define(CommitFactory)
{
    It("Accepts an input string and creates a commit")
    {
        commit_factory factory;

        std::vector<std::string> inputs;

        commit result = factory.create("x = foo(1)", "", inputs, "");

        AssertEqual("x = foo(1)", result.action());
    } Done

    It("Accepts a user and creates a commit")
    {
        commit_factory factory;

        std::vector<std::string> inputs;

        commit result = factory.create("", "me", inputs, "");

        AssertEqual("me", result.user());
    } Done

    It("Accepts a list of inputs and creates a commit")
    {
        commit_factory factory;

        std::vector<std::string> inputs = { "input1", "input2", "input3" };

        commit result = factory.create("", "", inputs, "");

        AssertElementsEqual(inputs, result.inputs());
    } Done

    It("Accepts an output and creates a commit")
    {
        commit_factory factory;

        std::vector<std::string> inputs;

        commit result = factory.create("", "", inputs, "output");

        AssertEqual("output", result.output());
    } Done

    It("Accepts an output and creates a commit")
    {
        commit_factory factory;

        std::vector<std::string> inputs;

        commit result = factory.create("", "", inputs, "output");

        AssertEqual("output", result.output());
    } Done
}
