#ifndef TELEGRAM_BOT_HPP
#define TELEGRAM_BOT_HPP

#include <string>
#include <telegram/net/HttpClient.hpp>
#include <telegram/types/Response.hpp>

using namespace Telegram::Net;

namespace Telegram {

class Bot {
public:
    Bot(const std::string&);

    [[nodiscard]] std::string getBaseUrl() const noexcept;

    // api
    Types::Response getMe();
private:
    std::string _api_token;
    std::string _base_url;
    HttpClient _httpClient;
}; // class Bot

} // namespace Telegram

#endif // TELEGRAM_BOT_HPP