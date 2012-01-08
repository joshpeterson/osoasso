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
        AssertEqual(std::string("object name"), tags.get("tag"));
    } Done

    It("Throws an exception when a tag is not found")
    {
        tag_repository tags;

        bool exception_occurred = false;
        std::string exception_message;
        try
        {
            tags.get("foo");
        }
        catch (const std::runtime_error& e)
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
        AssertEqual(std::string("object name 2"), tags.get("tag"));
    } Done
}
