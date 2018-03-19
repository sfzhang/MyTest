/**
 * @file Unit test for net client
 *
 * @author sfzhang
 * @date 208-3-12
 */

#include "inetstream.h"
#include "netclient.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

class MockINetStream: public INetStream {
public:
    MOCK_METHOD0(getString, std::string());
};

TEST(TestSuite_NetClient, parse)
{
    MockINetStream mock_net_strm;

    EXPECT_CALL(mock_net_strm, getString()).
        Times(1).WillOnce(Return(std::string()));

    NetClient net_client;
    ASSERT_FALSE(net_client.parse(mock_net_strm));
}

TEST(TestSuite_NetClient, parse_2)
{
    MockINetStream mock_net_strm;

    EXPECT_CALL(mock_net_strm, getString()).
        Times(1).WillOnce(Return(std::string("hello,gmock")));

    NetClient net_client;
    ASSERT_TRUE(net_client.parse(mock_net_strm));
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
