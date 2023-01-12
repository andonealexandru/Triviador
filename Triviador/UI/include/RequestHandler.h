#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class RequestHandler
{
public:
    explicit RequestHandler(const std::string& url);
    ~RequestHandler() = default;
    RequestHandler(const RequestHandler&) = default;
    RequestHandler& operator=(const RequestHandler&) = delete;

    cpr::Response Post(const std::string& endPoint, const std::string& body,
                       const std::pair<std::string, std::string>& header) const;
    cpr::Response Get(const std::string& endPoint, const std::pair<std::string, std::string>& header) const;

private:
    std::string m_url;
};
