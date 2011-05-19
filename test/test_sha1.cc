#include "../test_harness/test.h"
#include "../include/sha1.h"

using namespace osoasso;

TEST_FIXTURE_START(TestSHA1)

TEST_START(VerifyShortString)

    sha1 hasher;
    ASSERT_EQUAL("a9993e36 4706816a ba3e2571 7850c26c 9cd0d89d", hasher.hash());

TEST_END

TEST_FIXTURE_END
