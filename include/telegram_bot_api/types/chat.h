#ifndef TELEGRAM_BOT_API_TYPES_CHAT_H
#define TELEGRAM_BOT_API_TYPES_CHAT_H

#include <string>
#include <optional>

#include "nlohmann/json.hpp"

namespace TelegramBotApi {
namespace Types {

struct Chat {
    long long id;
    std::string type;
    std::optional<std::string> title;
    std::optional<std::string> username;
    std::optional<std::string> first_name;
    std::optional<std::string> last_name;
    std::optional<bool> is_forum;

    Chat() = default;
    Chat(long long id, const std::string& type) :
        id{id},
        type{type}
    {}
}; 

void from_json(const nlohmann::json&, Chat&);

void to_json(nlohmann::json&, const Chat&);

} // namespace Types
} // namespace TelegramBotApi

#endif // TELEGRAM_BOT_API_TYPES_CHAT_H