#include <string>
#include <stdexcept>
#include "../test_harness/test.h"
#include "../include/tree.h"

using namespace osoasso;

Define(Tree)
{
    It("Has a head node")
    {
        tree<std::string> test_tree;
        AssertEqual(std::string(), test_tree.head());
    } Done

    It("Allows insertion after the head node")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        AssertEqual("Foo", test_tree.head());
    } Done

    It("Allows the head node to be set")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.set_head("Foo");
        AssertEqual("Foo", test_tree.head());
    } Done

    It("Throws an exception if the new head does not exist")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");

        bool exception_occurred = false;
        try
        {
            test_tree.set_head("1");
        }
        catch (std::domain_error&)
        {
            exception_occurred = true;
        }

        AssertTrue(exception_occurred);
    } Done

    It("Has a begin method which exposes an iterator from the root")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");

        auto i = test_tree.begin();

        AssertEqual("Foo", *i);
    } Done

    It("Can be iterated from the root")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");

        auto i = test_tree.begin();
        ++i;

        AssertEqual("Bar", *i);
    } Done

    It("Has an end iterator")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");

        auto i = test_tree.begin();
        ++i;

        AssertTrue(i == test_tree.end());
    } Done

    It("Has an iterator that visits the first child added to the head first")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.set_head("Foo");

        test_tree.insert("Baz");

        auto i = test_tree.begin();
        ++i;

        AssertEqual("Bar", *i);
    } Done

    It("Has an iterator that visits the second child added to the head second")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.set_head("Foo");

        test_tree.insert("Baz");

        auto i = test_tree.begin();
        ++i; // Bar
        ++i;

        AssertEqual("Baz", *i);
    } Done

    It("Has a depth-first iterator")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.insert("Boo");
        test_tree.set_head("Foo");

        test_tree.insert("Baz");

        auto i = test_tree.begin();
        ++i; // Bar
        ++i;

        AssertEqual("Boo", *i);
    } Done

    It("Has a depth-first iterator that visits siblings")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.insert("Boo");
        test_tree.set_head("Foo");

        test_tree.insert("Baz");

        auto i = test_tree.begin();
        ++i; // Bar
        ++i; // Boo
        ++i;

        AssertEqual("Baz", *i);
    } Done

    It("Has a depth-first iterator that signals the end node correctly")
    {
        tree<std::string> test_tree;
        test_tree.insert("Foo");
        test_tree.insert("Bar");
        test_tree.insert("Boo");
        test_tree.set_head("Foo");

        test_tree.insert("Baz");

        auto i = test_tree.begin();
        ++i; // Bar
        ++i; // Boo
        ++i; // Baz
        ++i;

        AssertTrue(i == test_tree.end());
    } Done
}
