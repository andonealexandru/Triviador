#pragma once

#include <memory>
#include <string>
#include <crow.h>

namespace Server {
    class Player
    {
    public:
        // constructors
        Player() = default;
        Player(int id, const std::string& name);
        Player(const Player& other) = default;
        Player& operator=(const Player& other) = default;

        ~Player() = default;

        // getters
        int GetId() const;
        const std::string& GetName() const;

        // setters
        void SetId(int id);
        void SetName(const std::string& name);

    private:
        int m_id;
        std::string m_name;
    };
}