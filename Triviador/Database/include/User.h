#pragma once
#include <string>
#include <iostream>

namespace DB
{
    class User
    {
    public:
        // constructors
        User();

        User(std::string name);

        User(uint8_t id, std::string name);

        User(const User &other);

        User &operator=(const User &other);

        // getters
        uint8_t GetId();

        std::string GetName();

        // setters
        void SetId(uint8_t id);

        void SetName(std::string name);

    private:
        uint8_t mId;
        std::string mName;

    friend class DBAccess;
    };
}//namespace DB
