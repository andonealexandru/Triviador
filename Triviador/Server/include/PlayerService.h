#ifndef TRIVIADOR_PLAYERSERVICE_H
#define TRIVIADOR_PLAYERSERVICE_H

#include <unordered_map>

#include "Player.h"

namespace Server {
    class PlayerService {
    public:
        static PlayerService& GetInstance();

        bool PLayerExists(int id) const;
        Server::Player GetPlayer(int id) const;
        int GetNumberOfPlayers() const;
        std::unordered_map<int, Server::Player> GetPlayers() const;

        void AddPlayer(int id, Status status);
        void RemovePlayer(int id);

    private:
        PlayerService() {}

        int m_numberOfPlayers;
        std::unordered_map<int, Server::Player> m_players;

    public:
        PlayerService(PlayerService const&) = delete;
        void operator=(PlayerService const&) = delete;
    };
}

#endif //TRIVIADOR_PLAYERSERVICE_H
