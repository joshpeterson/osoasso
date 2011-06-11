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
