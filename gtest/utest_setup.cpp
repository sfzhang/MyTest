#include <gtest/gtest.h>
#include <iostream>

using namespace testing;
using namespace std;

/* Global SetUp() and TearDown() */
class MyEnv: public Environment {
public:

    virtual void SetUp()
    {
        cout << "MyEnv::SetUp(): Global SetUp()" << endl;
    }

    virtual void TearDown()
    {
        cout << "MyEnv::TearDown(): Global TearDown()" << endl;
    }
};

/* TestSuit SetUp() and TearDown() */
class FooTest: public ::testing::Test {
protected:
    /* Per-test-suit set-up */
    static void SetUpTestCase()
    {
        cout << "FooTest::SetUpTestCase(): TestSuit SetUp()" << endl;
    }

    /* Per-test-suit tear-down */
    static void TearDownTestCase()
    {
        cout << "FooTest::TearDown(): TestSuit TearDown()" << endl;
    }

    /* Per-test-case set-up */
    virtual void SetUp()
    {
        cout << "FooTest::SetUp(): TestCase SetUp()" << endl;
    }

    /* Per-test-case tear-down */
    virtual void TearDown()
    {
        cout << "FooTest::TearDown(): TestCase TearDown()" << endl;
    }
};

/* Use test fixture */
TEST_F(FooTest, test1)
{
    cout << "TestCase: test1" << endl;
    ASSERT_TRUE(1);
}

TEST_F(FooTest, test2)
{
    cout << "TestCase: test2" << endl;
    ASSERT_TRUE(true);
}

int main(int argc, char *argv[])
{
    InitGoogleTest(&argc, argv);
    AddGlobalTestEnvironment(new MyEnv);

    return RUN_ALL_TESTS();
}
