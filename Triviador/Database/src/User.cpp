#include <User.h>

namespace DB
{
    User::User(std::string name) : m_name(std::move(name))
    {}

    User::User(uint8_t id, std::string name) : m_id(id), m_name(std::move(name))
    {}

    User::User(const User &other)
    {
        m_id = other.m_id;
        m_name = other.m_name;
    }

    User &User::operator=(const User &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_name = other.m_name;
        }
        return *this;
    }

    uint8_t User::GetId()
    {
        return m_id;
    }

    std::string User::GetName()
    {
        return m_name;
    }

    void User::SetId(uint8_t id)
    {
        m_id = id;
    }

    void User::SetName(std::string name)
    {
        m_name = std::move(name);
    }
}//namespace DB