#pragma once
#include <vector>
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
        const std::vector<Server::Player>& GetPlayers() const;

        void AddPlayer(const Server::Player& player);

    private:
        std::vector<Server::Player> m_players;
    };
}