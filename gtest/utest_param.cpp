#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace testing;
using namespace std;

struct Data {
    int id;
    string name;
};

bool isValid(int id, const string &name)
{
    if ((id > 0) && (!name.empty())) {
        return true;
    }
    else {
        return false;
    }
}

/* Define param */
class IsValidParam: public ::testing::TestWithParam<Data> {};

/* Define Test case */
TEST_P(IsValidParam, test_isValid)
{
    auto data = GetParam();
    EXPECT_TRUE(isValid(data.id, data.name));
}

/* Instantiate */
INSTANTIATE_TEST_CASE_P(TestIsValid, IsValidParam,
    testing::Values(Data{ 1, "zsf" }, Data{ 2, "hly" }));
