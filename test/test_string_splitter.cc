#include <string>
#include <sstream>
#include "../test_harness/test.h"
#include "../include/string_splitter.h"

using namespace osoasso;

Define(StringSplitter)
{
    It("Returns the number of parts after splitting")
    {
        string_splitter splitter("The quick brown fox.", 4);
        AssertEqual(5, splitter.number_of_parts());
    } Done

    It("Returns the number of parts after splitting when the parts are not the same size")
    {
        string_splitter splitter("The quick brown fox.", 3);
        AssertEqual(7, splitter.number_of_parts());
    } Done

    It("Returns the correct first part of the string")
    {
        string_splitter splitter("The quick brown fox.", 4);
        AssertEqual(std::string("The "), splitter.part(0));
    } Done

    It("Returns the correct second part of the string")
    {
        string_splitter splitter("The quick brown fox.", 4);
        AssertEqual(std::string("quic"), splitter.part(1));
    } Done

    It("Returns the correct last part of the string")
    {
        string_splitter splitter("The quick brown fox.", 4);
        AssertEqual(std::string("fox."), splitter.part(4));
    } Done

    It("Returns the correct last part of the string when the parts are not the same size")
    {
        string_splitter splitter("The quick brown fox.", 3);
        AssertEqual(std::string("x."), splitter.part(6));
    } Done

    It("Returns the full string in the first part when the string is smaller than the part length")
    {
        string_splitter splitter("The quick brown fox.", 25);
        AssertEqual(std::string("The quick brown fox."), splitter.part(0));
    } Done

    It("Returns the correct number of parts with a very large string")
    {
        std::stringstream large_string;
        for  (int i = 0; i < 10000; ++i)
        {
            large_string << "fooba ";
        }

        string_splitter splitter(large_string.str(), 50000);
        AssertEqual(2, splitter.number_of_parts());
    } Done

    It("Returns correctly sized parts with a very large string")
    {
        std::stringstream large_string;
        for  (int i = 0; i < 10000; ++i)
        {
            large_string << "fooba ";
        }

        string_splitter splitter(large_string.str(), 50000);
        AssertEqual<size_t>(50000, splitter.part(0).size());
        AssertEqual<size_t>(10000, splitter.part(1).size());
    } Done
}
