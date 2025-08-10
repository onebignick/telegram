#ifndef TELEGRAM_TYPES_RESPONSE_HPP
#define TELEGRAM_TYPES_RESPONSE_HPP

#include <optional>
#include <variant>
#include <any>
#include <string>
#include "nlohmann/json.hpp"
#include "telegram/types/User.hpp"

namespace Telegram {
namespace Types {

struct ResponseParameters {
    std::optional<long long> migrate_to_chat_id;
    std::optional<long long> retry_after;
};

inline void from_json(const nlohmann::json& j, ResponseParameters& o) {
    if (j.contains("migrate_to_chat_id")) o.migrate_to_chat_id = j["migrate_to_chat_id"].template get<long long>();
    if (j.contains("retry_after")) o.retry_after = j["retry_after"].template get<long long>();
};

inline void to_json(nlohmann::json& j, const ResponseParameters& o) {
    if (o.migrate_to_chat_id) j["migrate_to_chat_id"] = o.migrate_to_chat_id;
    if (o.retry_after) j["retry_after"] = o.retry_after;
};

struct ResponseBase {
    bool ok;
};

template<typename T>
struct ResponseSuccess : public ResponseBase {
    T result;
};

struct ResponseFailure : public ResponseBase {
    long long error_code;
    std::string description;
    std::optional<ResponseParameters> parameters;
};

template<typename T>
using Response = std::variant<ResponseSuccess<T>, ResponseFailure>;

template <typename T>
inline void from_json(const nlohmann::json& j, ResponseSuccess<T>& o) {
    j.at("ok").get_to(o.ok);
    j.at("result").get_to(o.result);
};

template <typename T>
inline void to_json(nlohmann::json& j, const ResponseSuccess<T>& o) {
    j["ok"] = o.ok;
    j["result"] = o.result;
};

inline void from_json(const nlohmann::json& j, ResponseFailure& o) {
    j.at("ok").get_to(o.ok);
    j.at("error_code").get_to(o.error_code);
    j.at("description").get_to(o.description);
    
    if (j.contains("parameters")) o.parameters = j.at("parameters").template get<ResponseParameters>();
};

inline void to_json(nlohmann::json& j, const ResponseFailure& o) {
    j["ok"] = o.ok;
    j["error_code"] = o.error_code;
    j["description"] = o.description;

    if (o.parameters) j["parameters"] = o.parameters.value();
};

template <typename T>
inline void from_json(const nlohmann::json& j, Response<T>& o) {
    if (j.at("ok").get<bool>()) o = j.get<ResponseSuccess<T>>();
    else o = j.get<ResponseFailure>();
};

template <typename T>
inline void to_json(nlohmann::json& j, const Response<T>& o) {
    std::visit([&](auto&& arg) {
        to_json(j, arg);
    }, o);
};

} // namespace Types
} // namespace Telegram 

#endif // TELEGRAM_TYPES_RESPONSE_HPP