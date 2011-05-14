#ifndef __TEST_H
#define __TEST_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

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

#define TEST_FIXTURE_START \
    int main(int argc, char** argv)\
    {\
        bool all_tests_passed__ = true;

#define TEST_FIXTURE_END \
        return all_tests_passed__ ? 0 : 1;\
    }

#define TEST_START(test_name__) \
    std::cout << test_name__ << ": ";\
    try\
    {

#define TEST_END \
        std::cout << "passed" << std::endl;\
    }\
    catch(test_assertion_failed_exception__ &e)\
    {\
        std::cout << "failed" << std::endl;\
        std::cout << e.what() << std::endl;\
        all_tests_passed__ = false;\
    }

#define ASSERT_EQUAL(expected, actual) \
    if (expected != actual)\
    {\
        std::stringstream message;\
        message << "Expected: " << expected << std::endl;\
        message << "Actual: " << actual << std::endl;\
        message << __FILE__ << ":" << __LINE__ << std::endl;\
        throw test_assertion_failed_exception__(message.str().c_str());\
    }\

#endif // __TEST_H

