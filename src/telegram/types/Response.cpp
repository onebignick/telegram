#include <telegram/types/Response.hpp>


namespace Telegram {
namespace Types {

    void from_json(const nlohmann::json& j, ResponseSuccess& o) {
        j.at("ok").get_to(o.ok);
        j.at("result").get_to(o.result);
    };
    void to_json(nlohmann::json& j, const ResponseSuccess& o) {
        j["ok"] = o.ok;
        j["result"] = o.result;
    };

    void from_json(const nlohmann::json& j, ResponseFailure& o) {
        j.at("ok").get_to(o.ok);
        j.at("error_code").get_to(o.error_code);
        j.at("description").get_to(o.description);
        
        if (j.contains("parameters")) o.parameters = j["parameters"].template get<std::string>();
    };
    void to_json(nlohmann::json& j, const ResponseFailure& o) {
        j["ok"] = o.ok;
        j["error_code"] = o.error_code;
        j["description"] = o.description;

        if (o.parameters) j["parameters"] = o.parameters;
    };

    void from_json(const nlohmann::json& j, Response& o) {
        if (j.at("ok").get<bool>()) o = j.get<ResponseSuccess>();
        else o = j.get<ResponseFailure>();
    };
    void to_json(nlohmann::json& j, const Response& o) {
        std::visit([&](auto&& arg) {
            to_json(j, arg);
        }, o);
    };
}
}