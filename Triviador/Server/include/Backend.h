#pragma once

#include <unordered_set>

#include <User.h>
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
        void StartLoginRegister(crow::SimpleApp &app);
        void StartLobby(crow::SimpleApp &app);
        void StartGame(crow::SimpleApp &app);

        // getters
        const std::unordered_set<int>& GetPlayers() const;
        const Question &GetCurrentQuestion() const;

        void AddPlayer(int id);
        void SetNewCurrentQuestion();

    private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

        inline const std::string ToString(Status s);

        Status m_status;
        std::unordered_set<int> m_players;
        Server::Question m_currentQuestion;

	};
}