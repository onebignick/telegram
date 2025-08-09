#ifndef TELEGRAM_TYPES_RESPONSE_HPP
#define TELEGRAM_TYPES_RESPONSE_HPP

#include <optional>
#include <variant>
#include <any>
#include <string>
#include "nlohmann/json.hpp"

namespace Telegram {
namespace Types {

struct ResponseBase {
    bool ok;
};

struct ResponseSuccess : public ResponseBase {
    // todo variant for results
    nlohmann::json result;
};

struct ResponseFailure : public ResponseBase {
    long long error_code;
    std::string description;
    std::optional<std::string> parameters;
};

using Response = std::variant<ResponseSuccess, ResponseFailure>;

void from_json(const nlohmann::json& j, ResponseSuccess& o);
void to_json(nlohmann::json& j, const ResponseSuccess& o);

void from_json(const nlohmann::json& j, ResponseFailure& o);
void to_json(nlohmann::json& j, const ResponseFailure& o);

void from_json(const nlohmann::json& j, Response& o);
void to_json(nlohmann::json& j, const Response& o);

} // namespace Types
} // namespace Telegram 

#endif // TELEGRAM_TYPES_RESPONSE_HPP