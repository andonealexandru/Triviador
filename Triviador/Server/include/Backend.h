#pragma once

#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

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
            RegionQuestion,
            RegionChoice,
            WaitingForAnswers,
            MapChanged,
            Answer,
            AllPlayersAnswered,
            Duel,
        };
	public:

		Backend();
        void StartLoginRegister(crow::SimpleApp &app);
        void StartLobby(crow::SimpleApp &app);
        void StartGame(crow::SimpleApp &app);
        void StartDebugEndpoints(crow::SimpleApp &app);

        // getters
        const std::unordered_map<int, Status>& GetPlayers() const;
        const DB::Question &GetCurrentQuestion() const;

        void AddPlayer(int id, Status status);
        void GenerateNewMap();
        void SetNewCurrentQuestion(bool numeric = false);
        void AddPlayerAnswer(int id, int answer, int timeRemaining);
        void ErasePlayerAnswers();
        int ChangePlayerStatus(int playerId, Status status);
        int ChangeAllPlayersStatus(Status status);
        void GeneratePlayerRanking();

    private:
		Backend(Backend&&) = delete;
		Backend(const Backend&) = delete;
		Backend& operator=(Backend&&) = delete;
		Backend& operator=(const Backend&) = delete;

        inline const std::string ToString(Status s);

        Status m_status;
        std::unordered_map<int, Status> m_players;
        DB::Question m_currentQuestion;
        std::unordered_map<int, std::pair<int, int>> m_playerAnswers;
        std::vector<std::tuple<int, int, int>> m_playerRanking;
        Server::Map m_Map;
        std::unordered_set<int> m_usedQuestionIds;
	};
}