#include "telegram/Bot.hpp"
#include <telegram/types/Response.hpp>
#include <iostream>

const std::string BASE_API_URL = "https://api.telegram.org/bot";

using nlohmann::json;

namespace Telegram {

Bot::Bot(const std::string& api_token) {
    _api_token = std::move(api_token);
    _base_url = BASE_API_URL + _api_token;
}

std::string Bot::getBaseUrl() const noexcept {
    return _base_url;
}

Types::Response Bot::getMe() {
    const std::string api_url = _base_url + "/getMe";
    const std::string raw_response = _httpClient.request(api_url);
    json j = json::parse(raw_response);

    Types::Response response = j.template get<Types::Response>();
    return response;
}

} // namespace Telegram