#include "test.h"

int main(int argc, char** argv)
{
    bool all_tests_passed__ = true;
    int number_of_tests_run = 0;

    // Add RUN_TEST_FIXTURE statements here to run tests.
    RUN_TEST_FIXTURE(StressTestBlob)
    RUN_TEST_FIXTURE(StressTestMultiply)
    RUN_TEST_FIXTURE(StressTestRowIterator)
    RUN_TEST_FIXTURE(StressTestColumnIterator)

    return all_tests_passed__ ? 0 : 1;
}
