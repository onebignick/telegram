#ifndef TELEGRAM_HTTP_CLIENT_HPP
#define TELEGRAM_HTTP_CLIENT_HPP

#include <string>
#include <vector>

namespace Telegram {
namespace Net {

enum HttpRequestMethod {
    GET,
    POST,
}; // HttpRequestMethod

typedef std::vector<std::pair<std::string,std::string>> HttpRequestHeaders;

struct HttpRequestOptions {
    HttpRequestOptions() = default;

    HttpRequestMethod method = HttpRequestMethod::GET;
    HttpRequestHeaders headers = {};
    std::string body = "";
}; // HttpRequestArgs

class HttpClient {
public:
std::string request(const std::string& url, const HttpRequestOptions& opt = HttpRequestOptions());

private:

}; // HttpClient

} // namespace Net 
} // namespace Telegram 

#endif // TELEGRAM_HTTP_CLIENT_HPP