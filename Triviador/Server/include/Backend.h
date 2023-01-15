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
#include "Status.h"
#include "Player.h"

#define storage DB::DBAccess::GetInstance()

namespace Server
{
	
	class Backend
	{
	public:

		Backend();
        void StartLoginRegister(crow::SimpleApp &app);
        void StartLobby(crow::SimpleApp &app);
        void StartGame(crow::SimpleApp &app);
        void GamePowerups(crow::SimpleApp& app);
        void StartDebugEndpoints(crow::SimpleApp &app);

        // getters
        const std::unordered_map<int, Player>& GetPlayers() const;
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

        Status m_status;
        std::unordered_map<int, Player> m_players;
        // info about current question
        DB::Question m_currentQuestion;
        std::unordered_map<int, std::pair<int, int>> m_playerAnswers; // TODO: redundant information... remove one
        std::vector<std::tuple<int, int, int>> m_playerRanking; // id, answer, time remaining
        std::unordered_set<int> m_usedQuestionIds;
        // info about map
        std::unordered_map<int, int> m_playerRegionChoices;
        int m_attackedRegion;
        int m_attackerPlayerId;
        std::unordered_map<int, bool>  m_poweredUpUsers;
	};
}