#include "telegram_bot_api/types/user.h"

namespace TelegramBotApi {
namespace Types {

void from_json(const nlohmann::json& j, User& u) {
    j.at("id").get_to(u.id);
    j.at("is_bot").get_to(u.is_bot);
    j.at("first_name").get_to(u.first_name);

    // Optional fields
    if (j.contains("last_name") && !j["last_name"].is_null()) {
        u.last_name = j.at("last_name").get<std::string>(); // Get the string and assign
    } else {
        u.last_name.reset(); // Explicitly set to nullopt if key is missing or null
    }

    if (j.contains("username") && !j["username"].is_null()) {
        u.username = j.at("username").get<std::string>();
    } else {
        u.username.reset();
    }

    if (j.contains("language_code") && !j["language_code"].is_null()) {
        u.language_code = j.at("language_code").get<std::string>();
    } else {
        u.language_code.reset();
    }

    // For optional booleans, it's the same pattern
    if (j.contains("can_join_groups") && !j["can_join_groups"].is_null()) {
        u.can_join_groups = j.at("can_join_groups").get<bool>();
    } else {
        u.can_join_groups.reset();
    }

    if (j.contains("can_read_all_group_messages") && !j["can_read_all_group_messages"].is_null()) {
        u.can_read_all_group_messages = j.at("can_read_all_group_messages").get<bool>();
    } else {
        u.can_read_all_group_messages.reset();
    }

    if (j.contains("supports_inline_queries") && !j["supports_inline_queries"].is_null()) {
        u.supports_inline_queries = j.at("supports_inline_queries").get<bool>();
    } else {
        u.supports_inline_queries.reset();
    }
}

// to_json remains correct as it was
void to_json(nlohmann::json& j, const User& u) {
    j["id"] = u.id;
    j["is_bot"] = u.is_bot;
    j["first_name"] = u.first_name;

    if (u.last_name) {
        j["last_name"] = u.last_name.value();
    }
    if (u.username) {
        j["username"] = u.username.value();
    }
    if (u.language_code) {
        j["language_code"] = u.language_code.value();
    }
    if (u.can_join_groups) {
        j["can_join_groups"] = u.can_join_groups.value();
    }
    if (u.can_read_all_group_messages) {
        j["can_read_all_group_messages"] = u.can_read_all_group_messages.value();
    }
    if (u.supports_inline_queries) {
        j["supports_inline_queries"] = u.supports_inline_queries.value();
    }
}

} // namespace Types
} // namespace TelegramBotApi