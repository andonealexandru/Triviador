#pragma once

#include "crow.h"

#include "Player.h"

namespace Server
{
	
	class Backend
	{
    public:
        enum Status {
            InLobby,
            InGame,
            FirstQuestion,
            BaceChoice,
            SecondQuestion,
            RegionChoice
        };
	public:

		Backend();

        // getters
        const std::unordered_map<int, Server::Player>& GetPlayers() const;

        void AddPlayer(int id, const Server::Player& player);

	private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

        inline const std::string ToString(Status s);

        Status m_status;
        std::unordered_map<int, Server::Player> m_players;
	};
}