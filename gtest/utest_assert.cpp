#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace testing;
using namespace std;

TEST(TestSuit_assert, assert)
{
    ASSERT_TRUE(1);     // OK!
    ASSERT_FALSE(0);    // OK!

    ASSERT_TRUE(false); // failed!
    ASSERT_FALSE(true); // failed!
}

TEST(TestSuit_expect, expect)
{
    EXPECT_TRUE(1);     // OK!
    EXPECT_FALSE(0);    // OK!

    EXPECT_TRUE(false); // failed!
    EXPECT_FALSE(true); // failed!
}

TEST(TestSuit_append_message, append_message)
{
    EXPECT_TRUE(0) << "This is append message!";

    int i = 10;
    ASSERT_FALSE(i) << "i: " << i;
}

bool isOdd(int a)
{
    if (a % 2) {
        return true;
    }
    else {
        return false;
    }
}

TEST(TestSuit_predicate_assertion, predicate_assertion)
{
    int a = 2;
    EXPECT_TRUE(isOdd(a));

    EXPECT_PRED1(isOdd, a);
}

::testing::AssertionResult IsEven(int n){
  if ((n % 2) == 0)
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure() << n << " is odd";
}

TEST(TestSuit_assertion_result, assertion_result)
{
    int b = 1;
    EXPECT_TRUE(IsEven(1));
}

// 计算最大公约数
int Foo(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
    if (Foo(m, n) == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    msg << m_expr << " 和 " << n_expr << " 的最大公约数应该是：" << Foo(m, n) << " 而不是：" << k_expr;
    return testing::AssertionFailure(msg);
}

TEST(AssertFooTest, HandleFail)
{
    EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}
