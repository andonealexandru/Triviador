#include "Lobby.h"

const std::unordered_map<int, Server::Player>& Server::Lobby::GetPlayers() const
{
    return m_players;
}

void Server::Lobby::AddPlayer(const Server::Player& player)
{
    m_players.insert({ player.GetId(), player });
}