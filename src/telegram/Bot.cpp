#include "telegram/Bot.hpp"

const std::string BASE_API_URL = "https://api.telegram.org/bot";

namespace Telegram {

Bot::Bot(const std::string& api_token) {
    _api_token = std::move(api_token);
    _base_url = BASE_API_URL + _api_token;
}

std::string Bot::getBaseUrl() const {
    return _base_url;
}

} // namespace Telegram