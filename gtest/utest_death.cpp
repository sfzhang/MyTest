#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace testing;
using namespace std;

int read(int *p)
{
    return *p;
}

TEST(TestSuite_read_DeathTest, read1)
{
    ASSERT_DEATH(read(nullptr), "");
}
