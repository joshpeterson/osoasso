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
}
