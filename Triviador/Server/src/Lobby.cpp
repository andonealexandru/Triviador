#include "Lobby.h"

const std::vector<Server::Player>& Server::Lobby::GetPlayers() const
{
    return m_players;
}

void Server::Lobby::AddPlayer(const Server::Player& player)
{
    m_players.push_back(player);
}