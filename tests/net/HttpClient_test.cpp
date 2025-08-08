#include <telegram/net/HttpClient.hpp>
#include "gtest/gtest.h"

class HttpClientTest : public ::testing::Test {
protected:
    void SetUp() override {} 
    void TearDown() override {} 
};

using namespace Telegram::Net;
TEST_F(HttpClientTest, shouldReceiveResponseFromGetRequest) {
    const std::string url = "https://httpbin.org/get";
    HttpClient httpClient;
    const std::string response = httpClient.request(url);

    ASSERT_FALSE(response.empty());
    ASSERT_NE(response.find("\"url\": \"https://httpbin.org/get\""), std::string::npos);
}