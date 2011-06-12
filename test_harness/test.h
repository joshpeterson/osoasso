#ifndef __TEST_H
#define __TEST_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

class test_assertion_failed_exception__ : public std::exception
{
public:
    test_assertion_failed_exception__(const char* message) : message_(message) {}

    ~test_assertion_failed_exception__() throw() {}

    const char* what() const throw()
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

#define RUN_TEST_FIXTURE(test_fixture_name__) \
    std::cout << #test_fixture_name__ << ":" << std::endl;\
    void test_fixture_name__(bool& all_tests_passed__);\
    test_fixture_name__(all_tests_passed__);

#define Define(test_fixture_name__) void test_fixture_name__(bool& all_tests_passed__)

#define It(test_name__) \
    std::cout << "\t - " << test_name__ << std::endl;\
    try\

#define Done \
    catch(test_assertion_failed_exception__ &e)\
    {\
        std::cout << "\t\tFailed:" << std::endl;\
        std::cout << e.what() << std::endl;\
        all_tests_passed__ = false;\
    }

template <typename ComparisonType>
class AssertEqual
{
public:
    AssertEqual(ComparisonType expected, ComparisonType actual)
    {
        if (expected != actual)
        {
            std::stringstream message;
            message << "\t\t\tExpected: " << expected << std::endl;
            message << "\t\t\tActual:   " << actual << std::endl;
            throw test_assertion_failed_exception__(message.str().c_str());
        }
    }
};

template <>
class AssertEqual<std::string>
{
public:
    AssertEqual(std::string expected, std::string actual)
    {
        if (expected != actual)
        {
            std::stringstream message;
            message << "\t\t\tExpected: " << expected << std::endl;
            message << "\t\t\tActual:   " << actual << std::endl;

            if (expected.size() != actual.size())
            {
                message << "\t\t\tStrings differ in length, expected: " << expected.size() << " actual: " << actual.size() << std::endl;
            }
            else
            {
                message << "\t\t\t          ";
                for (size_t i = 0; i < expected.size(); ++i)
                {
                    if (expected[i] != actual[i])
                    {
                        message << "^" << std::endl;
                        message << "\t\t\tStrings differ at index " << i << std::endl;
                        break;
                    }
                    message << " ";
                }
            }

            throw test_assertion_failed_exception__(message.str().c_str());
        }
    }
};

template <typename ContainerType>
class AssertElementsEqual
{
public:
    AssertElementsEqual(ContainerType expected, ContainerType actual)
    {
        std::stringstream message;
        if (expected.size() != actual.size())
        {
            message << "\t\t\tVectors differ in length, expected: " << expected.size() << " actual: " << actual.size() << std::endl;

            throw test_assertion_failed_exception__(message.str().c_str());
        }
        else
        {
            for (size_t i = 0; i != expected.size(); ++i)
            {
                if (expected[i] != actual[i])
                {
                    message << "\t\t\tVectors differ at index " << i << std::endl;
                    message << "\t\t\tExpected: " << expected[i] << std::endl;
                    message << "\t\t\tActual:   " << actual[i] << std::endl;

                    throw test_assertion_failed_exception__(message.str().c_str());
                }
            }
        }
    }
};

class AssertTrue
{
public:
    AssertTrue(bool value)
    {
        if (!value)
        {
            std::stringstream message;
            message << "\t\t\tExpected true, but was false" << std::endl;

            throw test_assertion_failed_exception__(message.str().c_str());
        }
    }
};
#endif // __TEST_H

