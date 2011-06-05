#include <memory>
#include "../test_harness/test.h"
#include "../include/object_repository.h"
#include "mocks/mock_named_object.h"

using namespace osoasso;

TEST_FIXTURE_START(TestObjectRepository)

TEST_START(VerifyAdd)

    auto object1 = std::make_shared<mock_named_object>("Object 1");

    object_repository<mock_named_object> test_repo;
    test_repo.add(object1);
    ASSERT_EQUAL(object1, test_repo.get("Object 1"))

TEST_END

TEST_START(VerifyGetReturnsNULLForInvalidName)

    object_repository<mock_named_object> test_repo;
    ASSERT_EQUAL(NULL, test_repo.get("Object 1"))

TEST_END

TEST_START(VerifyAddWithTwoObjects)

    auto object1 = std::make_shared<mock_named_object>("Object 1");
    auto object2 = std::make_shared<mock_named_object>("Object 2");

    object_repository<mock_named_object> test_repo;
    test_repo.add(object1);
    test_repo.add(object2);
    ASSERT_EQUAL(object2, test_repo.get("Object 2"))

TEST_END

TEST_FIXTURE_END
