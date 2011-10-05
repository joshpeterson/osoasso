#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "../test_harness/test.h"
#include "../include/project_manager.h"

using namespace osoasso;

Define(ProjectManager)
{
    It("Returns the action of the last commit")
    {
        project_manager manager;
        manager.input("add([[1]], [[1]])", "me");

        AssertEqual("add([[1]], [[1]])", manager.get_last_commit().action);
    } Done

    It("Returns the user of the last commit")
    {
        project_manager manager;
        manager.input("add([[1]], [[1]])", "me");

        AssertEqual("me", manager.get_last_commit().user);
    } Done

    It("Returns the user of the last commit")
    {
        project_manager manager;
        manager.input("add([[1]], [[1]])", "me");

        AssertEqual("me", manager.get_last_commit().user);
    } Done

    It("Returns the time of the last commit")
    {
        project_manager manager;
        manager.input("add([[1]], [[1]])", "me");

        // Since the exact time will change, at least make sure it ii GMT
        std::string time = manager.get_last_commit().time;
        AssertEqual("GMT", time.substr(time.length() - 3));
    } Done
}
