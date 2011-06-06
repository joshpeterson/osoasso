#include "test.h"

int main(int argc, char** argv)
{
    bool all_tests_passed__ = true;

    // Add RUN_TEST_FIXTURE statements here to run tests.
    RUN_TEST_FIXTURE(TestBlob)
    RUN_TEST_FIXTURE(TestSHA1)
    RUN_TEST_FIXTURE(TestCommit)
    RUN_TEST_FIXTURE(TestObjectRepository)

    return all_tests_passed__ ? 0 : 1;
}
