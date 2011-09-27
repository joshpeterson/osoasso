#include <ctime>
#include <string>
#include <vector>
#include "../test_harness/test.h"
#include "../include/commit.h"

using namespace osoasso;

Define(Commit)
{
    It("Returns the correct action")
    {
        commit test_commit("foo", "me", 0, std::vector<std::string>(), ""); 
        AssertEqual("foo", test_commit.action());
    } Done

    It("Handles a complex action")
    {
        commit test_commit("x = inverse(a)", "me", 0, std::vector<std::string>(), ""); 
        AssertEqual("x = inverse(a)", test_commit.action());
    } Done

    It("Returns the correct user")
    {
        commit test_commit("foo", "me", 0, std::vector<std::string>(), ""); 
        AssertEqual("me", test_commit.user());
    } Done

    It("Handles a complex user")
    {
        commit test_commit("foo", "josh@mine.com", 0, std::vector<std::string>(), ""); 
        AssertEqual("josh@mine.com", test_commit.user());
    } Done

    It("Returns the correct time")
    {
        commit test_commit("foo", "me", 1306927001, std::vector<std::string>(), "");
        AssertEqual("Wed Jun  1 11:16:41 2011 GMT", test_commit.time());
    } Done

    It("Returns the correct time for a different time value")
    {
        commit test_commit("foo", "me", 1306927186, std::vector<std::string>(), "");
        AssertEqual("Wed Jun  1 11:19:46 2011 GMT", test_commit.time());
    } Done

    It("Returns the correct inputs")
    {
        std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
        commit test_commit("foo", "me", 0, test_inputs, "");

        std::vector<std::string> actual_inputs = test_commit.inputs();
        AssertElementsEqual(test_inputs, actual_inputs);
    } Done

    It("Returns the correct output")
    {
        commit test_commit("foo", "me", 0, std::vector<std::string>(), "TestOutput");
        AssertEqual("TestOutput", test_commit.output());
    } Done

    It("Returns the correct SHA1")
    {
        std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
        commit test_commit("foo", "me", 1306927186, test_inputs, "TestOutput");
        AssertEqual("b12c6f97 37cb129c b99b4d12 53c190d9 450325af", test_commit.name());
    } Done

    It("Can be made into a blob")
    {
        std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
        commit test_commit("foo", "me", 1306927186, test_inputs, "TestOutput");

        blob<char> test_blob = test_commit.make_blob();
        AssertEqual("b12c6f97 37cb129c b99b4d12 53c190d9 450325af", test_blob.name());
    } Done
}
