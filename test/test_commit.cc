#include "../test_harness/test.h"
#include "../include/commit.h"

using namespace osoasso;

TEST_FIXTURE_START(TestCommit)

    TEST_START(VerifyContents)

        commit test_commit("foo", "me"); 

    TEST_END

TEST_FIXTURE_END
