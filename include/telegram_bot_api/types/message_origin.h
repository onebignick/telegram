#ifndef TELEGRAM_BOT_API_H_MESSAGE_ORIGIN
#define TELEGRAM_BOT_API_H_MESSAGE_ORIGIN

#include <string>
#include <optional>
#include <variant>

#include "telegram_bot_api/types/chat.h"
#include "telegram_bot_api/types/user.h"
#include "nlohmann/json.hpp"

namespace TelegramBotApi {
namespace Types {

struct MessageOriginBase {
    std::string type;
    long long date;
};

struct MessageOriginUser : MessageOriginBase {
    User sender_user;
};

struct MessageOriginHiddenUser : MessageOriginBase {
    std::string sender_user;
};

struct MessageOriginChat : MessageOriginBase {
    Chat sender_chat;
    std::string author_signature;
};

struct MessageOriginChannel : MessageOriginBase {
    Chat chat;
    long long message_id;
    std::string author_signature;
};

using MessageOrigin = std::variant<
    MessageOriginUser,
    MessageOriginHiddenUser,
    MessageOriginChat,
    MessageOriginChannel
>;

void from_json(const nlohmann::json&, MessageOriginBase&);
void to_json(nlohmann::json&, const MessageOriginBase&);

void from_json(const nlohmann::json&, MessageOriginUser&);
void to_json(nlohmann::json&, const MessageOriginUser&);

void from_json(const nlohmann::json&, MessageOriginHiddenUser&);
void to_json(nlohmann::json&, const MessageOriginHiddenUser&);

void from_json(const nlohmann::json&, MessageOriginChat&);
void to_json(nlohmann::json&, const MessageOriginChat&);

void from_json(const nlohmann::json&, MessageOriginChannel&);
void to_json(nlohmann::json&, const MessageOriginChannel&);

} // namespace Types
} // namespace TelegramBotApi

#endif // TELEGRAM_BOT_API_H_MESSAGE_ORIGIN