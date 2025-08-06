#include "telegram_bot_api/types/chat.h"

namespace TelegramBotApi {
namespace Types {
    void from_json(const nlohmann::json& json, Chat& chat) {
        json.at("id").get_to(chat.id);
        json.at("type").get_to(chat.type);
        
        chat.title = json.value("title", "");
        chat.username = json.value("username", "");
        chat.first_name = json.value("first_name", "");
        chat.last_name = json.value("last_name", "");
        chat.is_forum = json.value("is_forum", false);
    }

    void to_json(nlohmann::json& json, const Chat& chat) {
        json["id"] = chat.id;
        json["type"] = chat.type;
        json["title"] = chat.title;
        json["username"] = chat.username;
        json["first_name"] = chat.first_name;
        json["last_name"] = chat.last_name;
        json["is_forum"] = chat.is_forum;
    }
} // namespace Types
} // namespace TelegramBotApi