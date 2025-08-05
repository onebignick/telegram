#ifndef TELEGRAM_BOT_API_TYPES_USER_H
#define TELEGRAM_BOT_API_TYPES_USER_H

#include <string>
#include <optional>
#include "nlohmann/json.hpp" // Assuming you've set up nlohmann/json

namespace TelegramBotApi {
namespace Types {

struct User {
    long long           id;
    bool                is_bot;
    std::string         first_name;
    std::optional<std::string> last_name;
    std::optional<std::string> username;
    std::optional<std::string> language_code;
    std::optional<bool> can_join_groups;
    std::optional<bool> can_read_all_group_messages;
    std::optional<bool> supports_inline_queries;

    // Default constructor
    User() = default;

    // Parameterized constructor for easy creation in tests
    User(long long id, bool is_bot, const std::string& first_name)
        : id(id), is_bot(is_bot), first_name(first_name) {}
};

// Function to deserialize JSON into a User object
void from_json(const nlohmann::json& j, User& u);

// Function to serialize a User object into JSON (optional, but good for testing)
void to_json(nlohmann::json& j, const User& u);

} // namespace Types
} // namespace TelegramBotApi

#endif // TELEGRAM_BOT_API_TYPES_USER_H