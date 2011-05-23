#include <vector>
#include "../test_harness/test.h"
#include "../include/sha1.h"

using namespace osoasso;

TEST_FIXTURE_START(TestSHA1)

TEST_START(VerifyShortString)

    sha1 hasher;
    std::vector<unsigned char> data = { 'a', 'b', 'c' };
    ASSERT_EQUAL("a9993e36 4706816a ba3e2571 7850c26c 9cd0d89d", hasher.hash(data));

TEST_END

TEST_START(VerifyLongString)

    sha1 hasher;
    std::vector<unsigned char> data = { 'a','b','c','d','b','c','d','e','c','d','e','f','d','e','f','g','e','f','g','h','f','g','h','i','g','h','i','j','h','i','j','k','i','j','k','l','j','k','l','m','k','l','m','n','l','m','n','o','m','n','o','p','n','o','p','q' };
    ASSERT_EQUAL("84983e44 1c3bd26e baae4aa1 f95129e5 e54670f1", hasher.hash(data));

TEST_END

TEST_FIXTURE_END
