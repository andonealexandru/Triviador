#include "RequestHandler.h"

RequestHandler::RequestHandler(const std::string& url)
    : m_url{ url }
{
}

cpr::Response RequestHandler::Post(const std::string &endPoint, const std::string &body,
                                   const std::pair<std::string, std::string> &header) const
{
    return  cpr::Post(cpr::Url{ m_url + endPoint },
                      cpr::Body{ body },
                      cpr::Header{{ header.first, header.second }});
}

cpr::Response RequestHandler::Get(const std::string &endPoint, const std::pair<std::string, std::string> &header) const
{
    return cpr::Get(cpr::Url{ m_url + endPoint },
                    cpr::Header{{ header.first, header.second }});
}
