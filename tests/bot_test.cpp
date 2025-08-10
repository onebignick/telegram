#include "gtest/gtest.h"
#include "telegram/Bot.hpp"

#include <iostream>

const std::string fail_api_token = "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11";

using namespace Telegram::Types;

class BotTest : public ::testing::Test {
protected:
    void SetUp() override {} 
    void TearDown() override {} 
};

TEST_F(BotTest, shouldConstructBaseUrl) {
    const std::string example_token = "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11";
    const std::string expected_base_url = "https://api.telegram.org/bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11";

    Telegram::Bot bot(example_token);

    ASSERT_EQ(expected_base_url, bot.getBaseUrl());
}

TEST_F(BotTest, shouldFailOnGetMe) {
    Telegram::Bot bot(fail_api_token);

    Response<User> response = bot.getMe();
    if (std::holds_alternative<ResponseFailure>(response)) {
        const auto& failure_response = std::get<ResponseFailure>(response);
        
        ASSERT_FALSE(failure_response.ok);
        ASSERT_EQ(401, failure_response.error_code);
        ASSERT_EQ("Unauthorized", failure_response.description);
    } else {
        const auto& success_response = std::get<ResponseSuccess<User>>(response);
        FAIL();
    }
}

TEST_F(BotTest, shouldSucceedOnGetMe) {
    Telegram::Bot bot(api_token);
    Response<User> response = bot.getMe();
    if (std::holds_alternative<ResponseFailure>(response)) {
        const auto& failure_response = std::get<ResponseFailure>(response);
        FAIL();
    } else {
        const auto& success_response = std::get<ResponseSuccess<User>>(response);
        ASSERT_TRUE(success_response.ok);
        ASSERT_TRUE(success_response.result.is_bot);
    }
}