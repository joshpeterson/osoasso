#include <memory>
#include "../test_harness/test.h"
#include "../include/object_repository.h"
#include "mocks/mock_named_object.h"

using namespace osoasso;

Define(ObjectRepository)
{
    It("An object can be added")
    {
        auto object1 = std::make_shared<mock_named_object>("Object 1");

        object_repository<mock_named_object> test_repo;
        test_repo.add(object1);
        AssertEqual<std::shared_ptr<mock_named_object>>(object1, test_repo.get("Object 1"));
    } Done

    It("Get returns NULL for an invalid object name")
    {
        object_repository<mock_named_object> test_repo;
        AssertEqual<std::shared_ptr<mock_named_object>>(std::shared_ptr<mock_named_object>(), test_repo.get("Object 1"));
    } Done

    It("Add works with two objects")
    {
        auto object1 = std::make_shared<mock_named_object>("Object 1");
        auto object2 = std::make_shared<mock_named_object>("Object 2");

        object_repository<mock_named_object> test_repo;
        test_repo.add(object1);
        test_repo.add(object2);
        AssertEqual<std::shared_ptr<mock_named_object>>(object2, test_repo.get("Object 2"));
    } Done
}
