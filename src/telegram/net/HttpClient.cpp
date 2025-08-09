#include <telegram/net/HttpClient.hpp>
#include "curl/curl.h"

#include <cstddef>
#include <string>

#include <iostream>

namespace Telegram {
namespace Net {

static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
    static_cast<std::string*>(userp)->append((char*)buffer, size*nmemb);
    return size * nmemb;
};

static std::string httpRequestMethodToString(const HttpRequestMethod& method) {
    if (method == HttpRequestMethod::GET) return "GET";
    if (method == HttpRequestMethod::POST) return "POST";
    return "";
}

std::string HttpClient::request(const std::string& url, const HttpRequestOptions& opt) {
    CURL* handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, httpRequestMethodToString(opt.method).c_str());
    
    struct curl_slist* headers = NULL;
    if (!opt.headers.empty()) {
        for (const auto& [key, value] : opt.headers) {
            std::string to_append = key + ": " + value;
            headers = curl_slist_append(headers, to_append.c_str());
        }
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
    }

    if (!opt.body.empty()) {
        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, opt.body.c_str());
    }

    std::string response;
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);

    auto res = curl_easy_perform(handle);

    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
    return response;
};

} // namespace Net 
} // namespace Telegram 
