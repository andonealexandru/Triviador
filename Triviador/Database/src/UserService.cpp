#include "UserService.h"

namespace DB
{
    UserService::UserService(const std::string& name) : m_name(name)
    {
    }

    UserService::UserService(const uint8_t id, const std::string& name) : m_id(id), m_name(name)
    {
    }

    UserService::UserService(const UserService &other)
    {
        m_id = other.m_id;
        m_name = other.m_name;
    }

    UserService &UserService::operator=(const UserService &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_name = other.m_name;
        }
        return *this;
    }

    uint8_t UserService::GetId() const { return m_id; }
    std::string UserService::GetName() const { return m_name; }

    void UserService::SetId(const uint8_t id) { m_id = id; }
    void UserService::SetName(const std::string& name) { m_name = name; }

}//namespace DB