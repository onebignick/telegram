#include <string>

#include "gtest/gtest.h"
#include "telegram_bot_api/types/chat.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
using TelegramBotApi::Types::Chat;

struct ChatTest : public ::testing::Test {

};

TEST_F(ChatTest, TestChatParsingMandatoryFieldsOnly) {
    const std::string json_string = R"({
        "id": 12345678,
        "type": "private"
    })";

    json j = json::parse(json_string);
    Chat chat;
    try {
        chat = j.get<Chat>();
    } catch (const json::exception& e) {
        FAIL() << "JSON parsing failed: " << e.what();
    }

    ASSERT_EQ(chat.id, 12345678);
    ASSERT_EQ(chat.type, "private");
}