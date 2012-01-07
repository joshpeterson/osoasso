#include <memory>
#include "../test_harness/test.h"
#include "../include/object_repository.h"

using namespace osoasso;

Define(ObjectRepository)
{
    It("An object can be added")
    {
        auto object1 = std::make_pair("Object 1", 3);

        object_repository<int> test_repo;
        test_repo.add(object1);
        AssertEqual(3, test_repo.get("Object 1"));
    } Done

    It("Get throws a domain error exception or an invalid object name")
    {
        object_repository<int> test_repo;
        
        bool exception_thrown = false;
        try
        {
            test_repo.get("Object 1");
        }
        catch(const std::domain_error&)
        {
            exception_thrown = true;
        }

        AssertTrue(exception_thrown);
    } Done

    It("Add works with two objects")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo;
        test_repo.add(object1);
        test_repo.add(object2);
        AssertEqual(4, test_repo.get("Object 2"));
    } Done

    It("Allows intialization with a list")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo = { object1, object2 };

        AssertEqual(3, test_repo.get("Object 1"));
        AssertEqual(4, test_repo.get("Object 2"));
    } Done

    It("Reports its size")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo = { object1, object2 };

        AssertEqual<size_t>(2, test_repo.size());
    } Done

    It("Does not add objects with duplicate names")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 1", 4);

        object_repository<int> test_repo;
        test_repo.add(object1);
        test_repo.add(object2);

        AssertEqual<size_t>(1, test_repo.size());
        AssertEqual(3, test_repo.get("Object 1"));
    } Done

    It("Does not add objects with duplicate names in the initializer list")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 1", 4);

        object_repository<int> test_repo = { object1, object2 };

        AssertEqual<size_t>(1, test_repo.size());
        AssertEqual(3, test_repo.get("Object 1"));
    } Done
}
