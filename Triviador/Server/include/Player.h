#pragma once

#include <memory>
#include <string>
#include <crow.h>

namespace Server {
    class Player
    {
    public:
        // constructors
        Player(int id, const std::string& name, crow::websocket::connection* connection);

        ~Player() = default;

        // getters
        int GetId() const;
        const std::string& GetName() const;
        crow::websocket::connection* GetConnection() const;

        // setters
        void SetId(int id);
        void SetName(const std::string& name);
        void SetConnection(crow::websocket::connection* connection);

    private:
        int m_id;
        std::string m_name;
        crow::websocket::connection* m_connection;
    };
}