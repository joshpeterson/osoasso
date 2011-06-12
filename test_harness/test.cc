#include "test.h"

int main(int argc, char** argv)
{
    bool all_tests_passed__ = true;

    // Add RUN_TEST_FIXTURE statements here to run tests.
    RUN_TEST_FIXTURE(Blob)
    RUN_TEST_FIXTURE(SHA1)
    RUN_TEST_FIXTURE(Commit)
    RUN_TEST_FIXTURE(ObjectRepository)
    RUN_TEST_FIXTURE(CommandParser)

    return all_tests_passed__ ? 0 : 1;
}

void AssertEqual(std::string expected, std::string actual)
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

void AssertTrue(bool value)
{
    if (!value)
    {
        std::stringstream message;
        message << "\t\t\tExpected true, but was false" << std::endl;

        throw test_assertion_failed_exception__(message.str().c_str());
    }
}
