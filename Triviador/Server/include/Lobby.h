#pragma once
#include <unordered_map>
#include "Player.h"

namespace Server
{
    class Lobby
    {
    public:
        // constructors
        Lobby() = default;

        ~Lobby() = default;

        // getters
        const std::unordered_map<int, Server::Player>& GetPlayers() const;

        void AddPlayer(const Server::Player& player);

    private:
        std::unordered_map<int, Server::Player> m_players;
    };
}