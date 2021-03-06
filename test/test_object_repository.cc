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
        AssertEqual(3, test_repo.get("Object 1").get_value());
    } Done

    It("Get throws a domain error exception or an invalid object name")
    {
        object_repository<int> test_repo;
        
        bool exception_thrown = false;
        try
        {
            test_repo.get("Object 1").get_value();
        }
        catch(const std::runtime_error&)
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
        AssertEqual(4, test_repo.get("Object 2").get_value());
    } Done

    It("Allows intialization with a list")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo(2, { object1, object2 });

        AssertEqual(3, test_repo.get("Object 1").get_value());
        AssertEqual(4, test_repo.get("Object 2").get_value());
    } Done

    It("Reports its size")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo(2, { object1, object2 });

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
        AssertEqual(3, test_repo.get("Object 1").get_value());
    } Done

    It("Does not add objects with duplicate names in the initializer list")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 1", 4);

        object_repository<int> test_repo(2, { object1, object2 });

        AssertEqual<size_t>(1, test_repo.size());
        AssertEqual(3, test_repo.get("Object 1").get_value());
    } Done

    It("Returns a list of keys")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo(2, { object1, object2 });

        std::vector<std::string> names = test_repo.get_keys();
        AssertEqual(std::string("Object 1"), names[0]);
        AssertEqual(std::string("Object 2"), names[1]);
    } Done

    It("Returns a list of values")
    {
        auto object1 = std::make_pair("Object 1", 3);
        auto object2 = std::make_pair("Object 2", 4);

        object_repository<int> test_repo(2, { object1, object2 });

        std::vector<int> values = test_repo.get_values();
        AssertEqual(3, values[0]);
        AssertEqual(4, values[1]);
    } Done
}
