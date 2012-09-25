#include <iostream>
#include <ctime>
#include "test.h"
#include "../include/timer.h"

int main(int argc, char** argv)
{
    bool all_tests_passed__ = true;
    int number_of_tests_run = 0;

    osoasso::timer test_timer;

    // Add RUN_TEST_FIXTURE statements here to run tests.
    RUN_TEST_FIXTURE(Blob)
    RUN_TEST_FIXTURE(SHA1)
    RUN_TEST_FIXTURE(Commit)
    RUN_TEST_FIXTURE(StringSplitter)
    RUN_TEST_FIXTURE(ObjectRepository)
    RUN_TEST_FIXTURE(TagRepository)
    RUN_TEST_FIXTURE(CommandParser)
    RUN_TEST_FIXTURE(Matrix)
    RUN_TEST_FIXTURE(MatrixElementIterator)
    RUN_TEST_FIXTURE(MatrixRowIterator)
    RUN_TEST_FIXTURE(MatrixColumnIterator)
    RUN_TEST_FIXTURE(MatrixParser)
    RUN_TEST_FIXTURE(MatrixBuilder)
    RUN_TEST_FIXTURE(MatrixBlobber)
    RUN_TEST_FIXTURE(MatrixIteratorWithSize)
    RUN_TEST_FIXTURE(MatrixFormatter)
    RUN_TEST_FIXTURE(DoubleEqual)
    RUN_TEST_FIXTURE(CommandFactory)
    RUN_TEST_FIXTURE(CommandDispatcher)
    RUN_TEST_FIXTURE(Tree)
    RUN_TEST_FIXTURE(CommitFactory)
    RUN_TEST_FIXTURE(ProjectManager)
    RUN_TEST_FIXTURE(HelpManager)
    RUN_TEST_FIXTURE(Osoasso)
    RUN_TEST_FIXTURE(ParallelTask)
    RUN_TEST_FIXTURE(MaxOffDiagonalIndex)
    RUN_TEST_FIXTURE(Add)
    RUN_TEST_FIXTURE(Subtract)
    RUN_TEST_FIXTURE(Multiply)
    RUN_TEST_FIXTURE(Random)
    RUN_TEST_FIXTURE(Transpose)
    RUN_TEST_FIXTURE(RandomSymmetric)
    RUN_TEST_FIXTURE(Identity)

    if (all_tests_passed__)
    {
        std::cout << "\nRan " << number_of_tests_run << " tests in " << test_timer.elapsed() << "s.\n";
    }

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

void AssertFalse(bool value)
{
    if (value)
    {
        std::stringstream message;
        message << "\t\t\tExpected false, but was true" << std::endl;

        throw test_assertion_failed_exception__(message.str().c_str());
    }
}

