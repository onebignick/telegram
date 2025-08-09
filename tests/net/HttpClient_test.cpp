#include <telegram/net/HttpClient.hpp>
#include "gtest/gtest.h"

class HttpClientTest : public ::testing::Test {
protected:
    void SetUp() override {} 
    void TearDown() override {} 
};

using namespace Telegram::Net;
TEST_F(HttpClientTest, shouldReceiveResponsesFromHttpRequests) {
    HttpClient httpClient;
    const std::string get_response = httpClient.request("https://httpbin.org/get");

    ASSERT_FALSE(get_response.empty());
    ASSERT_NE(get_response.find("\"url\": \"https://httpbin.org/get\""), std::string::npos);

    HttpRequestOptions opt;
    opt.method = HttpRequestMethod::POST;
    opt.headers = {
        {"Content-Type", "application/json"}
    };
    opt.body = R"({
        "test": "test"
    })";
    const std::string response = httpClient.request("https://httpbin.org/post", opt);
    std::cout << response << std::endl;

    ASSERT_FALSE(response.empty());
    ASSERT_NE(response.find(R"("test": "test")"), std::string::npos);
    ASSERT_NE(response.find(R"("Content-Type": "application/json")"), std::string::npos);
    ASSERT_NE(response.find(R"("url": "https://httpbin.org/post")"), std::string::npos);
}