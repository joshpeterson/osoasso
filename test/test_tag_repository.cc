#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/tag_repository.h"

using namespace osoasso;

Define(TagRepository)
{
    It("Can accept a new tag and get the object name associated with it")
    {
        tag_repository tags;
        tags.add("tag", "object name");
        AssertEqual(std::string("object name"), tags.get("tag").get_value());
    } Done

    It("Throws an exception when a tag is not found")
    {
        tag_repository tags;

        bool exception_occurred = false;
        std::string exception_message;
        try
        {
            tags.get("foo").get_value();
        }
        catch (const std::runtime_error& e)
        {
            exception_occurred = true;
            exception_message = e.what();
        }
        catch (const std::exception& e)
        {
            exception_occurred = true;
            exception_message = e.what();
        }

        AssertTrue(exception_occurred);
        AssertEqual(std::string("The tag foo does not exist."), exception_message);
    } Done

    It("Replaces the value of an existing tag")
    {
        tag_repository tags;
        tags.add("tag", "object name");
        tags.add("tag", "object name 2");
        AssertEqual(std::string("object name 2"), tags.get("tag").get_value());
    } Done

    It("Has a contains check that does not throw an exception when a tag does not exist")
    {
        tag_repository tags;
        AssertFalse(tags.contains("foo"));
    } Done

    It("Has a contains check that returns true when a tag does exist")
    {
        tag_repository tags;
        tags.add("foo", "bar");
        AssertTrue(tags.contains("foo"));
    } Done

    It("Returns a zero count when it has no tags")
    {
        tag_repository tags;

        AssertEqual<size_t>(0, tags.count());
    } Done

    It("Returns the number of tags it has")
    {
        tag_repository tags;

        tags.add("foo", "bar");
        tags.add("foo1", "bar1");

        AssertEqual<size_t>(2, tags.count());
    } Done
}
