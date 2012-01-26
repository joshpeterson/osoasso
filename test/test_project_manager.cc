#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "../test_harness/test.h"
#include "../include/project_manager.h"
#include "../include/matrix.h"

using namespace osoasso;

Define(ProjectManager)
{
    It("Returns the action of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        AssertEqual("add([[1]], [[1]])", data.action);
    } Done

    It("Returns the user of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        AssertEqual("me", data.user);
    } Done

    It("Returns the user of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        AssertEqual("me", data.user);
    } Done

    It("Returns the time of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        // Since the exact time will change, at least make sure it is GMT.
        std::string time = data.time;
        AssertEqual("GMT", time.substr(time.length() - 3));
    } Done

    It("Returns the name of the output of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        AssertEqual("c155be83 bedce48e f48618cf 2cc4cbdf 7c569897", data.output);
    } Done

    It("Returns a non-empty string for the name of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("add([[1]], [[1]])", "me");

        // The name of the commit will change each time we run.
        AssertTrue(data.name != std::string());
    } Done

    It("Returns the tag of the last commit")
    {
        project_manager manager;
        commit_data data = manager.input("tag = add([[1]], [[1]])", "me");

        AssertEqual(std::string("tag"), data.tag);
    } Done

    It("Provides access to the matrix repository")
    {
        matrix<double> expected_output = { { 3.0, 7.0 } };
        project_manager manager;
        commit_data data = manager.input("add([[1 2]], [[2 5]])", "me");

        std::string output = data.output;

        std::shared_ptr<const matrix<double>> actual_output = manager.get_matrix(output);

        AssertElementsEqual(expected_output, *actual_output);
    } Done
}
