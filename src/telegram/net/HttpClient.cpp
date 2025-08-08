#include <telegram/net/HttpClient.hpp>
#include "curl/curl.h"

#include <cstddef>
#include <string>

namespace Telegram {
namespace Net {

static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    static_cast<std::string*>(userp)->append((char*)buffer, size*nmemb);
    return size * nmemb;
};

std::string HttpClient::request(const std::string& url, const HttpRequestOptions& opt) {
    CURL* handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

    std::string response;
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);

    auto res = curl_easy_perform(handle);
    return response;
};

} // namespace Net 
} // namespace Telegram 
