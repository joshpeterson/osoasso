#include <ctime>
#include <string>
#include <vector>
#include "../test_harness/test.h"
#include "../include/commit.h"

using namespace osoasso;

TEST_FIXTURE_START(TestCommit)

TEST_START(VerifyAction)

    commit test_commit("foo", "me", 0, std::vector<std::string>(), ""); 
    ASSERT_EQUAL("foo", test_commit.action())

TEST_END

TEST_START(VerifyComplexAction)

    commit test_commit("x = inverse(a)", "me", 0, std::vector<std::string>(), ""); 
    ASSERT_EQUAL("x = inverse(a)", test_commit.action())

TEST_END

TEST_START(VerifyUser)

    commit test_commit("foo", "me", 0, std::vector<std::string>(), ""); 
    ASSERT_EQUAL("me", test_commit.user())

TEST_END

TEST_START(VerifyComplexUser)

    commit test_commit("foo", "josh@mine.com", 0, std::vector<std::string>(), ""); 
    ASSERT_EQUAL("josh@mine.com", test_commit.user())

TEST_END

TEST_START(VerifyTime)

    commit test_commit("foo", "me", 1306927001, std::vector<std::string>(), "");
    ASSERT_EQUAL(std::string("Wed Jun  1 11:16:41 2011 GMT"), test_commit.time())

TEST_END

TEST_START(VerifyAnotherTime)

    commit test_commit("foo", "me", 1306927186, std::vector<std::string>(), "");
    ASSERT_EQUAL(std::string("Wed Jun  1 11:19:46 2011 GMT"), test_commit.time())

TEST_END

TEST_START(VerifyInputs)

    std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
    commit test_commit("foo", "me", 0, test_inputs, "");

    std::vector<std::string> actual_inputs = test_commit.inputs();
    ASSERT_EQUAL(test_inputs.size(), actual_inputs.size())
    for (auto i = test_inputs.cbegin(), j = actual_inputs.cbegin(); i != test_inputs.cend(); ++i, ++j)
    {
        ASSERT_EQUAL(*i, *j)
    }

TEST_END

TEST_START(VerifyOutput)

    commit test_commit("foo", "me", 0, std::vector<std::string>(), "TestOutput");

    ASSERT_EQUAL("TestOutput", test_commit.output())

TEST_END

TEST_START(VerifyName)

    std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
    commit test_commit("foo", "me", 1306927186, test_inputs, "TestOutput");

    ASSERT_EQUAL("b12c6f97 37cb129c b99b4d12 53c190d9 450325af", test_commit.name())

TEST_END

TEST_START(VerifyMakeBlob)

    std::vector<std::string> test_inputs = { "input1", "input2", "input3" };
    commit test_commit("foo", "me", 1306927186, test_inputs, "TestOutput");

    blob<char> test_blob = test_commit.make_blob();

    ASSERT_EQUAL("b12c6f97 37cb129c b99b4d12 53c190d9 450325af", test_blob.name())

TEST_END

TEST_FIXTURE_END
