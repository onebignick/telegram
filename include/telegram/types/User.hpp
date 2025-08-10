#ifndef TELEGRAM_TYPES_USER_HPP
#define TELEGRAM_TYPES_USER_HPP

#include <string>
#include <optional>
#include <nlohmann/json.hpp>

namespace Telegram {
namespace Types {

class User {

public:
    long long id;
    bool is_bot;
    std::string first_name;
    std::optional<std::string> last_name;
    std::optional<std::string> username;
    std::optional<std::string> language_code;
    std::optional<bool> is_premium;
    std::optional<bool> added_to_attachment_menu;
    std::optional<bool> can_join_groups;
    std::optional<bool> can_read_all_group_messages;
    std::optional<bool> supports_inline_queries;
    std::optional<bool> can_connect_to_business;
    std::optional<bool> has_main_web_app;

    User() = default;
};

inline void from_json(const nlohmann::json& j, User& o) {
    j.at("id").get_to(o.id);
    j.at("is_bot").get_to(o.is_bot);
    j.at("first_name").get_to(o.first_name);

    if (j.contains("last_name")) j.at("last_name").template get<std::string>();
    if (j.contains("username")) j.at("username").template get<std::string>();
    if (j.contains("language_code")) j.at("language_code").template get<std::string>();
    if (j.contains("is_premium")) j.at("is_premium").template get<bool>();
    if (j.contains("added_to_attachment_menu")) j.at("added_to_attachment_menu").template get<bool>();
    if (j.contains("can_join_groups")) j.at("can_join_groups").template get<bool>();
    if (j.contains("can_read_all_group_messages")) j.at("can_read_all_group_messages").template get<bool>();
    if (j.contains("supports_inline_queries")) j.at("supports_inline_queries").template get<bool>();
    if (j.contains("can_connect_to_business")) j.at("can_connect_to_business").template get<bool>();
    if (j.contains("has_main_web_app")) j.at("has_main_web_app").template get<bool>();
}

// Explicitly define to_json for User
inline void to_json(nlohmann::json& j, const User& o) {
    j["id"] = o.id;
    j["is_bot"] = o.is_bot;
    j["first_name"] = o.first_name;

    if (o.last_name) j["last_name"] = o.last_name.value();
    if (o.username) j["username"] = o.username.value();
    if (o.language_code) j["language_code"] = o.language_code.value();
    if (o.is_premium) j["is_premium"] = o.is_premium.value();
    if (o.added_to_attachment_menu) j["added_to_attachment_menu"] = o.added_to_attachment_menu.value();
    if (o.can_join_groups) j["can_join_groups"] = o.can_join_groups.value();
    if (o.can_read_all_group_messages) j["can_read_all_group_messages"] = o.can_read_all_group_messages.value();
    if (o.supports_inline_queries) j["supports_inline_queries"] = o.supports_inline_queries.value();
    if (o.can_connect_to_business) j["can_connect_to_business"] = o.can_connect_to_business.value();
    if (o.has_main_web_app) j["has_main_web_app"] = o.has_main_web_app.value();
}

} // namespace Types
} // namespace Telegram

#endif // TELEGRAM_TYPES_USER_HPP