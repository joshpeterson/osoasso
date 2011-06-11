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
        ASSERT_EQUAL(object1, test_repo.get("Object 1"))

    } Done

    It("Get returns NULL for an invalid object name")
    {

        object_repository<mock_named_object> test_repo;
        ASSERT_EQUAL(NULL, test_repo.get("Object 1"))

    } Done

    It("Add works with two objects")
    {
        auto object1 = std::make_shared<mock_named_object>("Object 1");
        auto object2 = std::make_shared<mock_named_object>("Object 2");

        object_repository<mock_named_object> test_repo;
        test_repo.add(object1);
        test_repo.add(object2);
        ASSERT_EQUAL(object2, test_repo.get("Object 2"))

    } Done
}
