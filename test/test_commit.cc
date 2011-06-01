#include <ctime>
#include <string>
#include "../test_harness/test.h"
#include "../include/commit.h"

using namespace osoasso;

TEST_FIXTURE_START(TestCommit)

TEST_START(VerifyAction)

    commit test_commit("foo", "me", 0); 
    ASSERT_EQUAL("foo", test_commit.action())

TEST_END

TEST_START(VerifyUser)

    commit test_commit("foo", "me", 0); 
    ASSERT_EQUAL("me", test_commit.user())

TEST_END

TEST_START(VerifyTime)

    commit test_commit("foo", "me", 1306927001);
    ASSERT_EQUAL(std::string("Wed Jun  1 11:16:41 2011"), test_commit.time())

TEST_END

TEST_START(VerifyAnotherTime)

    commit test_commit("foo", "me", 1306927186);
    ASSERT_EQUAL(std::string("Wed Jun  1 11:19:46 2011"), test_commit.time())

TEST_END

TEST_FIXTURE_END
