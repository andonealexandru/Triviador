#pragma once

#include <unordered_set>

#include <User.h>
#include "crow.h"

#include "DBAccess.h"
#include "Map.h"

namespace Server
{
	
	class Backend
	{
    public:
        enum Status {
            InLobby,
            PlayersModified,
            InGame,
            StartNewGame,
            FirstQuestion,
            BaseChoice,
            SecondQuestion,
            RegionChoice,
            WaitingForAnswers,
            MapChanged,
        };
	public:

		Backend();
        void StartLoginRegister(crow::SimpleApp &app);
        void StartLobby(crow::SimpleApp &app);
        void StartGame(crow::SimpleApp &app);

        // getters
        const std::unordered_map<int, Status>& GetPlayers() const;
        const DB::Question &GetCurrentQuestion() const;

        void AddPlayer(int id, Status status);
        void GenerateNewMap();
        void SetNewCurrentQuestion(bool numeric = false);

    private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

        inline const std::string ToString(Status s);

        Status m_status;
        std::unordered_map<int, Status> m_players;
        DB::Question m_currentQuestion;
        Server::Map m_Map;
	};
}