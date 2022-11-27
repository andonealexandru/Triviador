#pragma once
#include <string>
#include <iostream>

namespace DB
{
    class UserService
    {
    public:
        // constructors
        UserService() = default;

        explicit UserService(const std::string& name);
        UserService(const uint8_t id, const std::string& name);
        UserService(const UserService &other);
        UserService &operator=(const UserService &other);

        // getters
        uint8_t GetId() const;
        std::string GetName() const;

        // setters
        void SetId(const uint8_t id);
        void SetName(const std::string& name);

    public:
        uint8_t m_id;
        std::string m_name;
    };
}//namespace DB

