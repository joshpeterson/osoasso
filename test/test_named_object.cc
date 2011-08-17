#include "../test_harness/test.h"
#include "../include/named_object.h"

using namespace osoasso;

Define(NamedObject)
{
    It("Associates a name with an object")
    {
        named_object<int> test("Test Name", 5);
        AssertEqual("Test Name", test.name());
    } Done

    It("Provides the value of the object")
    {
        named_object<int> test("Test Name", 5);
        AssertEqual(5, test.value());
    } Done

    It("Has a make function for template deduction")
    {
        named_object<int> test = make_named_object("Test Name", 5);
        AssertEqual(5, test.value());
    } Done
}
