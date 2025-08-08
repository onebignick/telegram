#include "gtest/gtest.h"
#include "telegram/Bot.hpp"

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