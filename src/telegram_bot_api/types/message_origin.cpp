#include <telegram_bot_api/types/message_origin.h>

namespace TelegramBotApi {
namespace Types {

void from_json(const nlohmann::json& j, MessageOriginBase& o) {
    j.at("type").get_to(o.type);
    j.at("date").get_to(o.date);
};
void to_json(nlohmann::json& j, const MessageOriginBase& o) {
    j["type"] = o.type;
    j["date"] = o.date;
};

void from_json(const nlohmann::json& j, MessageOriginUser& o) {
    from_json(j, static_cast<MessageOriginBase&>(o));
    j.at("sender_user").get_to(o.sender_user);
};
void to_json(nlohmann::json& j, const MessageOriginUser& o) {
    to_json(j, static_cast<const MessageOriginBase&>(o));
    j["sender_user"] = o.sender_user;
};

void from_json(const nlohmann::json& j, MessageOriginHiddenUser& o) {
    from_json(j, static_cast<MessageOriginBase&>(o));
    j.at("sender_user").get_to(o.sender_user);
};
void to_json(nlohmann::json& j, const MessageOriginHiddenUser& o) {
    to_json(j, static_cast<const MessageOriginBase&>(o));
    j["sender_user"] = o.sender_user;
};

void from_json(const nlohmann::json& j, MessageOriginChat& o) {
    from_json(j, static_cast<MessageOriginBase&>(o));
    j.at("sender_chat").get_to(o.sender_chat);
    j.at("author_signature").get_to(o.author_signature);
};
void to_json(nlohmann::json& j, const MessageOriginChat& o) {
    to_json(j, static_cast<const MessageOriginBase&>(o));
    j["sender_chat"] = o.sender_chat;
    j["author_signature"] = o.author_signature;
};

void from_json(const nlohmann::json& j, MessageOriginChannel& o) {
    from_json(j, static_cast<MessageOriginBase&>(o));
    j.at("chat").get_to(o.chat);
    j.at("message_id").get_to(o.message_id);
    j.at("author_signature").get_to(o.author_signature);
};
void to_json(nlohmann::json& j, const MessageOriginChannel& o) {
    to_json(j, static_cast<const MessageOriginBase&>(o));
    j["chat"] = o.chat;
    j["message_id"] = o.message_id;
    j["author_signature"] = o.author_signature;
};

} // Types
} // TelegramBotApi