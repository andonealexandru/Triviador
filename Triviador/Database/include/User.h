#pragma once

#include <string>
#include <iostream>

namespace DB
{
    class User
    {
    public:
        // constructors
        User() = default;

        explicit User(const std::string& name);
        User(const uint32_t id, const std::string& name);
        User(const User& other) = default;
        User& operator=(const User& other) = default;
        ~User() = default;
       

        // getters
        uint32_t GetId() const;
        std::string GetName() const;
        std::string GetPassword() const;

        // setters
        void SetId(const uint32_t id);
        void SetName(const std::string& name);
        void SetPassword(const std::string& password);

    private:
        uint32_t m_id;
        std::string m_name;
        std::string m_password;
    };
}//namespace DB

