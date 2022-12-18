#pragma once

#include "crow.h"

#include "Player.h"
#include "Question.h"

namespace Server
{
	
	class Backend
	{
    public:
        enum Status {
            InLobby,
            PlayersModified,
            InGame,
            WaitingForPlayers,
            FirstQuestion,
            BaseChoice,
            SecondQuestion,
            RegionChoice,
            WaitingForAnswers,
        };
	public:

		Backend();

        // getters
        const std::unordered_map<int, Server::Player>& GetPlayers() const;
        const Question &GetCurrentQuestion() const;

        void AddPlayer(int id, const Server::Player& player);
        void SetNewCurrentQuestion();

    private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

        inline const std::string ToString(Status s);

        Status m_status;
        std::unordered_map<int, Server::Player> m_players;
        Server::Question m_currentQuestion;
	};
}