#include "gtest/gtest.h"
#include "telegram_bot_api/types/user.h"
#include "nlohmann/json.hpp"
#include <string>
#include <optional>

// For convenience
using nlohmann::json;
using TelegramBotApi::Types::User;

// Test fixture for User tests (optional, but good for common setup/teardown)
struct UserTest : public ::testing::Test {
    // You could put common setup here if needed
};

TEST_F(UserTest, TestUserParsingFullFields) {
    const std::string json_str = R"({
        "id": 123456789,
        "is_bot": false,
        "first_name": "John",
        "last_name": "Doe",
        "username": "john_doe",
        "language_code": "en",
        "can_join_groups": true,
        "can_read_all_group_messages": false,
        "supports_inline_queries": true
    })";

    json j = json::parse(json_str);
    User user;
    try {
        user = j.get<User>(); // Use nlohmann/json's convenience conversion
    } catch (const json::exception& e) {
        FAIL() << "JSON parsing failed: " << e.what();
    }

    ASSERT_EQ(user.id, 123456789);
    ASSERT_FALSE(user.is_bot);
    ASSERT_EQ(user.first_name, "John");
    ASSERT_TRUE(user.last_name.has_value());
    ASSERT_EQ(user.last_name.value(), "Doe");
    ASSERT_TRUE(user.username.has_value());
    ASSERT_EQ(user.username.value(), "john_doe");
    ASSERT_TRUE(user.language_code.has_value());
    ASSERT_EQ(user.language_code.value(), "en");
    ASSERT_TRUE(user.can_join_groups.has_value());
    ASSERT_TRUE(user.can_join_groups.value());
    ASSERT_TRUE(user.can_read_all_group_messages.has_value());
    ASSERT_FALSE(user.can_read_all_group_messages.value());
    ASSERT_TRUE(user.supports_inline_queries.has_value());
    ASSERT_TRUE(user.supports_inline_queries.value());
}

TEST_F(UserTest, TestUserParsingMandatoryFieldsOnly) {
    const std::string json_str = R"({
        "id": 987654321,
        "is_bot": true,
        "first_name": "MyBot"
    })";

    json j = json::parse(json_str);
    User user;
    try {
        user = j.get<User>();
    } catch (const json::exception& e) {
        FAIL() << "JSON parsing failed: " << e.what();
    }

    ASSERT_EQ(user.id, 987654321);
    ASSERT_TRUE(user.is_bot);
    ASSERT_EQ(user.first_name, "MyBot");

    // Optional fields should not have values
    ASSERT_FALSE(user.last_name.has_value());
    ASSERT_FALSE(user.username.has_value());
    ASSERT_FALSE(user.language_code.has_value());
    ASSERT_FALSE(user.can_join_groups.has_value());
    ASSERT_FALSE(user.can_read_all_group_messages.has_value());
    ASSERT_FALSE(user.supports_inline_queries.has_value());
}

TEST_F(UserTest, TestUserParsingWithNullOptionalFields) {
    const std::string json_str = R"({
        "id": 111111111,
        "is_bot": false,
        "first_name": "Jane",
        "last_name": null,
        "username": null,
        "language_code": "es",
        "can_join_groups": null
    })";

    json j = json::parse(json_str);
    User user;
    try {
        user = j.get<User>();
    } catch (const json::exception& e) {
        FAIL() << "JSON parsing failed: " << e.what();
    }

    ASSERT_EQ(user.id, 111111111);
    ASSERT_FALSE(user.is_bot);
    ASSERT_EQ(user.first_name, "Jane");

    // Null optional fields should result in std::nullopt
    ASSERT_FALSE(user.last_name.has_value());
    ASSERT_FALSE(user.username.has_value());

    // Populated optional field
    ASSERT_TRUE(user.language_code.has_value());
    ASSERT_EQ(user.language_code.value(), "es");

    // Null boolean optional field
    ASSERT_FALSE(user.can_join_groups.has_value());
    ASSERT_FALSE(user.can_read_all_group_messages.has_value()); // Not in JSON, should be nullopt
    ASSERT_FALSE(user.supports_inline_queries.has_value()); // Not in JSON, should be nullopt
}

TEST_F(UserTest, TestUserSerializationFullFields) {
    User user;
    user.id = 123456789;
    user.is_bot = false;
    user.first_name = "John";
    user.last_name = "Doe";
    user.username = "john_doe";
    user.language_code = "en";
    user.can_join_groups = true;
    user.can_read_all_group_messages = false;
    user.supports_inline_queries = true;

    json j = user; // Use nlohmann/json's convenience conversion

    ASSERT_EQ(j["id"], 123456789);
    ASSERT_EQ(j["is_bot"], false);
    ASSERT_EQ(j["first_name"], "John");
    ASSERT_EQ(j["last_name"], "Doe");
    ASSERT_EQ(j["username"], "john_doe");
    ASSERT_EQ(j["language_code"], "en");
    ASSERT_EQ(j["can_join_groups"], true);
    ASSERT_EQ(j["can_read_all_group_messages"], false);
    ASSERT_EQ(j["supports_inline_queries"], true);
}

TEST_F(UserTest, TestUserSerializationMandatoryFieldsOnly) {
    User user;
    user.id = 987654321;
    user.is_bot = true;
    user.first_name = "MyBot";

    json j = user;

    ASSERT_EQ(j["id"], 987654321);
    ASSERT_EQ(j["is_bot"], true);
    ASSERT_EQ(j["first_name"], "MyBot");

    // Optional fields should not be present in the JSON
    ASSERT_FALSE(j.contains("last_name"));
    ASSERT_FALSE(j.contains("username"));
    ASSERT_FALSE(j.contains("language_code"));
    ASSERT_FALSE(j.contains("can_join_groups"));
    ASSERT_FALSE(j.contains("can_read_all_group_messages"));
    ASSERT_FALSE(j.contains("supports_inline_queries"));
}

TEST_F(UserTest, TestUserParsingAndSerializationRoundtrip) {
    const std::string original_json_str = R"({
        "id": 123,
        "is_bot": false,
        "first_name": "Test",
        "username": "test_user",
        "supports_inline_queries": true
    })";

    // 1. Parse from JSON
    json initial_j = json::parse(original_json_str);
    User user = initial_j.get<User>();

    // 2. Serialize back to JSON
    json reserialized_j = user;

    // 3. Compare parsed and then re-serialized JSON with the original
    // nlohmann::json can compare objects directly, ignoring whitespace
    ASSERT_EQ(initial_j, reserialized_j);
}

// You would also need a main function for your tests, usually in tests/main_test.cpp
/*
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/