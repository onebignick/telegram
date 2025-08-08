#ifndef TELEGRAM_BOT_HPP
#define TELEGRAM_BOT_HPP

#include <string>

namespace Telegram {

class Bot {
public:
    Bot(const std::string&);

    std::string getBaseUrl() const;
private:
    std::string _api_token;
    std::string _base_url;
}; // class Bot

} // namespace Telegram

#endif // TELEGRAM_BOT_HPP