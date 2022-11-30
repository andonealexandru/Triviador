#include "User.h"

namespace DB
{
    User::User(const std::string& name) : m_name(name)
    {
    }

    User::User(const uint32_t id, const std::string& name) : m_id(id), m_name(name)
    {
    }

    uint32_t User::GetId() const { return m_id; }
    std::string User::GetName() const { return m_name; }
    std::string User::GetPassword() const { return m_password; }

    void User::SetId(const uint32_t id) { m_id = id; }
    void User::SetName(const std::string& name) { m_name = name; }
    void User::SetPassword(const std::string& password) { m_password = password; }

}//namespace DB