#undef NDEBUG
#define NDEBUG
#include <base/assert.h>

#include <base/string_utils.h>

#include <third_party/gtest/exported/include/gtest/gtest.h>

namespace dist_clang {
namespace base {

TEST(AssertReleaseTest, FailureStackTrace) {
  // FIXME: a gtest implementation-dependent test.
  const String expected = EscapeRegex(
      "Assertion failed: false\n"
      "  dist_clang::base::AssertReleaseTest_FailureStackTrace_Test::TestBody"
      "()\n"
      "  void testing::internal::HandleSehExceptionsInMethodIfSupported<testing"
      "::Test, void>(testing::Test*, void (testing::Test::*)(), char const*)\n"
      "  void testing::internal::HandleExceptionsInMethodIfSupported<testing::T"
      "est, void>(testing::Test*, void (testing::Test::*)(), char const*)\n"
      "  testing::Test::Run()\n"
      "  testing::TestInfo::Run()\n"
      "  testing::TestCase::Run()\n"
      "  testing::internal::UnitTestImpl::RunAllTests()\n"
      "  bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing"
      "::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool "
      "(testing::internal::UnitTestImpl::*)(), char const*)\n"
      "  bool testing::internal::HandleExceptionsInMethodIfSupported<testing::i"
      "nternal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool "
      "(testing::internal::UnitTestImpl::*)(), char const*)\n"
      "  testing::UnitTest::Run()\n"
      "  RUN_ALL_TESTS()\n"
      "  main\n");
  ASSERT_THROW_STD(CHECK(false), expected);
  ASSERT_NO_THROW(DCHECK(false));
  ASSERT_NO_THROW(DCHECK_O_EVAL(false));
  // |NOTREACHED()| has undefined behavior - don't test it.
}

TEST(AssertReleaseTest, ExpressionEvaluation) {
  int i = 0;
  auto expr = [](int& a) -> bool {
    ++a;
    return false;
  };
  ASSERT_NO_THROW(DCHECK_O_EVAL(expr(i)));
  ASSERT_EQ(1, i);
}

}  // namespace base
}  // namespace dist_clang
