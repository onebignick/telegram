#include "gtest/gtest.h"
#include "telegram/Bot.hpp"

// example from telegram
const std::string api_token = "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11";

using namespace Telegram::Types;

void process_response(const Response& response) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, ResponseSuccess>) {
            std::cout << "Result: " << arg.result << std::endl;
        } else if constexpr (std::is_same_v<T, ResponseFailure>) {
            std::cout << "Error Code: " << arg.error_code << std::endl;
            std::cout << "Description: " << arg.description << std::endl;
        }
    }, response);
}

class BotTest : public ::testing::Test {
protected:
    void SetUp() override {} 
    void TearDown() override {} 
};

TEST_F(BotTest, shouldConstructBaseUrl) {
    const std::string expected_base_url = "https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11";

    Telegram::Bot bot(api_token);

    ASSERT_EQ(expected_base_url, bot.getBaseUrl());
}

TEST_F(BotTest, shouldCallGetMe) {
    Telegram::Bot bot(api_token);

    Response response = bot.getMe();
    process_response(response);

    ASSERT_EQ(true, false);
}