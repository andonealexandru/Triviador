#include "Backend.h"
#include "Player.h"
#include "Question.h"
#include "DBAccess.h"
#include "User.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <random>

void Server::Backend::StartLoginRegister(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/users/register")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        // check for body
                        auto body = crow::json::load(req.body);
                        if (!body)
                            return crow::response(400);

                        // check for user in DB
                        auto users = storage->GetUserByUsername<DB::User>(body["name"].s());
                        if (!users.empty())
                            return crow::response(409);

                        // create user
                        DB::User new_user(body["name"].s(), body["password"].s());
                        auto id = storage->Insert(new_user);

                        return crow::response(
                                201,
                                crow::json::wvalue{{ "ID", id }}
                                ); // created
                    });

    CROW_ROUTE(app, "/users/login")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        // check for body
                        auto body = crow::json::load(req.body);
                        if (!body)
                            return crow::response(400);

                        // check for user in DB
                        auto users = storage->GetUserByUsername<DB::User>(body["name"].s());
                        if (users.empty())
                            return crow::response(409);

                        // check password
                        if (users.front().GetPassword() != body["password"].s())
                            return crow::response(401);

                        return crow::response(
                                200,
                                crow::json::wvalue{{ "ID", users.front().GetId() }}
                        );
                    });

    CROW_ROUTE(app, "/users/profile")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        const auto userStatistics = storage->GetUserStatistics<DB::UserStatistics>(id);
        const bool noStatistics = userStatistics.empty();

        return crow::json::wvalue{
                {"games", noStatistics ? 0 : userStatistics.front().GetGameCount()},
                {"wins",  noStatistics ? 0 : userStatistics.front().GetWonGames()}
        };
    });
}

void Server::Backend::StartLobby(crow::SimpleApp &app) {
    /**
     * InLobby - nothing needs to be done
     * PlayersModified - should call /lobby/players to update player list
     * InGame - game started, should join game
     */
    CROW_ROUTE(app, "/lobby")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        if (m_status == Status::InLobby)
            return crow::json::wvalue{
                {"status", m_players.find(id) == m_players.end() ? ToString(m_status) : ToString(m_players.find(id)->second.GetStatus())}
        };
        return crow::json::wvalue{{ "status", ToString(Status::InGame) }};
    });

    /// get list of all players in lobby
    CROW_ROUTE(app, "/lobby/players")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        ChangePlayerStatus(id, Status::InLobby);

        std::vector<crow::json::wvalue> res_json;

        for (const auto& player : m_players) {
            res_json.push_back(crow::json::wvalue{
                    {"id", player.first},
                    {"name", player.second.GetUser()->GetName()}
            });
        }

        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "players", res_json }
        };
    });

    /// join lobby
    CROW_ROUTE(app, "/lobby/join")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        auto header = req.get_header_value("ID");
                        int id = std::stoi(header);

                        // check if user already in lobby
                        auto player = m_players.find(id);
                        if (player != m_players.end())
                            return crow::response(400);

                        // add user in lobby
                        AddPlayer(id, Status::InLobby);
                        // change all other users to playersModified
                        ChangeAllPlayersStatus(Status::PlayersModified);
                        return crow::response(200);
                    });

    /// leave lobby
    CROW_ROUTE(app, "/lobby/leave")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        auto header = req.get_header_value("ID");
                        int id = std::stoi(header);

                        // check if user in lobby
                        auto player = m_players.find(id);
                        if (player == m_players.end())
                            return crow::response(400);

                        // erase user from lobby
                        m_players.erase(player);
                        // change all other users to playersModified
                        ChangeAllPlayersStatus(Status::PlayersModified);
                        return crow::response(200);
                    });
}

void Server::Backend::StartGame(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/game")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        return crow::json::wvalue{
                {"status",
                 m_players.find(id) == m_players.end() ? ToString(Status::InGame) : ToString(m_players.find(id)->second.GetStatus())}
        };
    });

    CROW_ROUTE(app, "/game/players")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res_json;

        for (const auto& player : m_players) {
            res_json.push_back(crow::json::wvalue{
                    {"id", player.first},
                    {"playerId", player.second.GetId()},
                    {"name", player.second.GetUser()->GetName()},
                    {"score", player.second.GetScore()}
            });
        }

        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "players", res_json }
        };
    });

    CROW_ROUTE(app, "/game/start").methods("POST"_method)([&](const crow::request& req) {
        m_status = Status::StartNewGame;
        ChangeAllPlayersStatus(Status::StartNewGame);

        GenerateNewMap();

        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/map/first")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::InGame);

        bool allGotMap = true;
        for (const auto& player : m_players)
            if (player.second.GetStatus() != InGame)
                allGotMap = false;

        if (allGotMap) {
            m_status = Status::BaseChoice;
            ChangeAllPlayersStatus(Status::FirstQuestion);
            SetNewCurrentQuestion(true);
        }

        return crow::json::wvalue{ {"mapId", m_Map.GetId()} };
    });

    CROW_ROUTE(app, "/game/firstQuestion")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::Answer);

        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "question", m_currentQuestion.GetQuestion() },
                { "type", m_currentQuestion.GetType() }
        };
    });

    CROW_ROUTE(app, "/game/answer").methods("POST"_method)([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        ChangePlayerStatus(id, Status::WaitingForAnswers);

        AddPlayerAnswer(id, body["answer"].i(), body["timeRemaining"].i());

        if (m_playerAnswers.size() == m_players.size() || m_status == Status::Duel && m_playerAnswers.size() == 2)
        {
            if (!m_poweredUpUsers.empty())
            {
                ChangeAllPlayersStatus(Status::InGame);
                for (const auto &player: m_poweredUpUsers)
                {
                    ChangePlayerStatus(player.first, Status::PowerupRegionChoice);
                }
            }
            else
            {
                GeneratePlayerRanking();
                ChangeAllPlayersStatus(Status::AllPlayersAnswered);
            }
        }

        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/allAnswers")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;

        for (const auto& player : m_playerRanking) {
            res.push_back(crow::json::wvalue{
                    {"id", std::get<0>(player)},
                    {"name", m_players[std::get<0>(player)].GetUser()->GetName()},
                    {"answer", GetAnswerAsString(std::get<1>(player))}, // TODO: get answer as string
                    {"timeRemaining", std::get<2>(player)}
            });
        }

        bool allPlayersReceived = true;
        int playerNumber = m_players.size();

        switch (m_status) {
            case Status::BaseChoice: /// BASE CHOICE PHASE
                ChangePlayerStatus(id, Status::InGame);
                // wait for all players to turn InGame
                allPlayersReceived = true;
                for (const auto& player : m_players)
                    if (player.second.GetStatus() != Status::InGame) {
                        allPlayersReceived = false;
                        break;
                    }

                if (allPlayersReceived) // first players chooses base
                    ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::BaseChoice);
                break;

            case Status::RegionChoice: /// REGION CHOICE PHASE
                ChangePlayerStatus(id, Status::InGame);
                // wait for all players to turn InGame
                allPlayersReceived = true;
                for (const auto& player : m_players)
                    if (player.second.GetStatus() != Status::InGame) {
                        allPlayersReceived = false;
                        break;
                    }

                if (allPlayersReceived) {
                    // update m_playerRegionChoices based on m_playerRanking aka how many
                    for (int place = 0; place < playerNumber; ++place) {
                        if (playerNumber - place - 1 > 0)
                            m_playerRegionChoices.emplace(std::get<0>(m_playerRanking[place]), playerNumber - place - 1);
                    }
                    ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::RegionChoice);
                }
                break;

            case Status::Duel: /// DUEL PHASE
                ChangePlayerStatus(id, Status::InGame);

                allPlayersReceived = true;
                for (const auto& player : m_players)
                    if (player.second.GetStatus() != Status::InGame) {
                        allPlayersReceived = false;
                        break;
                    }

                if (allPlayersReceived) {
                    //ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::RegionChoice);
                    if (std::get<0>(m_playerRanking.front()) == m_Map.GetRegion(m_attackedRegion)->GetUserId()) { // if attacked user won
                        m_Map.GetRegion(m_attackedRegion)->IncrementScore();
                        m_players[m_Map.GetRegion(m_attackedRegion)->GetUserId()].IncrementScore();
                    }
                    else { // attacked user lost
                        if (m_Map.GetRegion(m_attackedRegion)->GetScore() == 100) {
                            if (!m_Map.GetRegion(m_attackedRegion)->IsBase()) {
                                m_players[m_Map.GetRegion(m_attackedRegion)->GetUserId()].DecrementScore();
                                m_Map.GetRegion(m_attackedRegion)->SetUserId(std::get<0>(m_playerRanking.front()));
                                m_players[m_Map.GetRegion(m_attackedRegion)->GetUserId()].IncrementScore();
                            }
                            else { // lost base
                                // TODO: handle in endgame
                                int loser = m_Map.GetRegion(m_attackedRegion)->GetUserId();
                                m_players[m_attackerPlayerId].SetScore(m_players[m_attackerPlayerId].GetScore() + m_players[loser].GetScore());
                                m_players[loser].SetScore(0);
                                m_finishedPlayers.push_back(m_players[loser]);
                                m_players.erase(loser);
                                m_Map.GetRegion(m_attackedRegion)->DestroyBase();
                                m_Map.ChangeRegionsOwners(loser, m_attackerPlayerId);
                                // if only one player remains
                                if (m_players.size() == 1) {
                                    ChangeAllPlayersStatus(Status::Endgame);
                                }
                            }
                        }
                        else {
                            m_Map.GetRegion(m_attackedRegion)->DecrementScore();
                            m_players[m_Map.GetRegion(m_attackedRegion)->GetUserId()].DecrementScore();
                        }
                    }
                    ChangeAllPlayersStatus(Status::MapChanged);
                    m_attackerPlayerId++;
                    if (m_players.find(m_attackerPlayerId) == m_players.end())
                        m_attackerPlayerId++;
                    if (m_attackerPlayerId >= m_players.size() + 1) { // finished one round
                        m_attackerPlayerId = 1;
                        m_Map.RoundPlayed();
                        if (m_Map.GetRounds() == 0) {
                            ChangeAllPlayersStatus(Status::Endgame);
                            break;
                        }
                    }
                    for (const auto& player : m_players) {
                        if (player.second.GetId() == m_attackerPlayerId) {
                            ChangePlayerStatus(player.first, Status::Duel);
                        }
                    }
                }
                break;
            default:
                break;
        }

        return crow::json::wvalue{
            { "answers", res },
            { "correctAnswer", GetCorrectAnswerAsString() }
        };
    });

    CROW_ROUTE(app, "/game/baseChoice")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;
        const auto& validChoices = m_Map.GetValidBaseChoices();

        for (const auto& validChoice : validChoices) {
            res.emplace_back(validChoice);
        }

        return crow::response( crow::json::wvalue{ res } );
    });

    CROW_ROUTE(app, "/game/baseChoice").methods("POST"_method)([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        // check if player making call is the first player in the list
        if (id != std::get<0>(m_playerRanking.front()))
            return crow::response(403);

        m_Map.GetRegions()[body["base"].i() - 1]->MakeBase();
        m_Map.GetRegions()[body["base"].i() - 1]->SetUserId(id);
        m_players[id].SetScore(300);

        // all players need to update map
        ChangeAllPlayersStatus(Status::MapChanged);

        // erase first player from list
        if (!m_playerRanking.empty())
            m_playerRanking.erase(m_playerRanking.cbegin());

        if (!m_playerRanking.empty())
            ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::BaseChoice);
        else {// all players have base, starting RegionChoice
            m_status = Status::RegionChoice;
            SetNewCurrentQuestion(true);
            ChangeAllPlayersStatus(Status::RegionQuestion);
        }
        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/map")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        switch (m_players.find(id)->second.GetStatus()) {
            case Status::MapChanged:
                ChangePlayerStatus(id, Status::InGame);
                break;
            default:
                break;
        }

        std::vector<crow::json::wvalue> res;

        const auto& regions =  m_Map.GetRegions();
        for (const auto& region : regions) {
            res.push_back(crow::json::wvalue{
                    { "id", region->GetId() },
                    { "userId", region->GetUserId() },
                    { "isBase", region->IsBase() },
                    { "score", region->GetScore() }
            });
        }

        return crow::json::wvalue{ res };
    });

    CROW_ROUTE(app, "/game/regionQuestion")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::Answer);

        return crow::json::wvalue{
                { "status", ToString(m_status)},
                { "question", m_currentQuestion.GetQuestion()},
                { "type", m_currentQuestion.GetType()}
        };
    });

    CROW_ROUTE(app, "/game/regionChoice")([&](const crow::request &req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;
        const auto& validChoices = m_Map.GetValidRegionChoices(id);

        for (const auto& validChoice : validChoices) {
            res.emplace_back(validChoice);
        }

        return crow::response( crow::json::wvalue{ res } );
    });

    CROW_ROUTE(app, "/game/regionChoice").methods("POST"_method)([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        // check if player making call is the first player in the list
        if (id != std::get<0>(m_playerRanking.front()))
            return crow::response(403);

        m_Map.GetRegions()[body["region"].i() - 1]->SetUserId(id);
        m_Map.GetRegions()[body["region"].i() - 1]->IncrementScore();
        m_players[id].IncrementScore();

        // all players need to update map
        ChangeAllPlayersStatus(Status::MapChanged);

        m_playerRegionChoices[id]--;
        // erase first player from list
        if (!m_playerRanking.empty() && m_playerRegionChoices[id] == 0) {
            m_playerRanking.erase(m_playerRanking.cbegin());
            m_playerRegionChoices.erase(id);
        }

        if (!m_playerRanking.empty() && !m_playerRegionChoices.empty())
            ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::RegionChoice);
        else if (!m_Map.AllRegionsOccupied()) {
            m_playerRegionChoices.clear();
            m_status = Status::RegionChoice;
            ChangeAllPlayersStatus(Status::RegionQuestion);
            SetNewCurrentQuestion(true);
        }
        else {// all players have all regions
            m_attackedRegion = -1;
            m_status = Status::Duel;
            SetNewCurrentQuestion();
            m_attackerPlayerId = 1;
            ChangeAllPlayersStatus(Status::MapChanged);
            for (const auto& player : m_players) {
                if (player.second.GetId() == m_attackerPlayerId) {
                    ChangePlayerStatus(player.first, Status::Duel);
                }
            }
        }
        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/attackRegion")([&](const crow::request &req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;
        const auto& validChoices = m_Map.GetValidRegionToAttack(id);

        for (const auto& validChoice : validChoices) {
            res.emplace_back(validChoice);
        }

        return crow::response( crow::json::wvalue{ res } );
    });

    CROW_ROUTE(app, "/game/attackRegion").methods("POST"_method)([&](const crow::request &req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        m_attackedRegion = body["region"].i() - 1;
        int attackedUser = m_Map.GetRegion(m_attackedRegion)->GetUserId();

        SetNewCurrentQuestion();
        ChangePlayerStatus(id, Status::AttackQuestion);
        ChangePlayerStatus(attackedUser, Status::AttackQuestion);

        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/attackQuestion")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::Answer);

        if (m_currentQuestion.GetType() == "single_choice") {

            return crow::json::wvalue{
                    {"status",   ToString(m_status)},
                    {"question", m_currentQuestion.GetQuestion()},
                    {"type",     m_currentQuestion.GetType()}
            };
        }
        else {
            std::vector<crow::json::wvalue> choices;

            for (const auto &choice: DB::DBAccess::GetInstance()->GetQuestionChoices<DB::QuestionChoice>(
                    m_currentQuestion.GetId())) {
                choices.push_back(crow::json::wvalue{
                        {"choice", choice.GetChoice()},
                        {"id", choice.GetId()}
                });
            }

            return crow::json::wvalue{
                    {"status",   ToString(m_status)},
                    {"question", m_currentQuestion.GetQuestion()},
                    {"type",     m_currentQuestion.GetType()},
                    {"choices",  crow::json::wvalue{ choices }}
            };
        }
    });

    CROW_ROUTE(app, "/game/endgame")([&](const crow::request& req) {
        auto players = GetOrderedPlayers();

        std::vector<crow::json::wvalue> res;

        bool first = true;
        for (const auto& player : players) {
            if (!m_addedStatisticsInDB) {
                bool updated = false;
                std::vector<DB::UserStatistics> userStatistics = storage->GetAll<DB::UserStatistics>();
                if (!userStatistics.empty()) {
                    for (const auto &statistic: userStatistics) {
                        if (statistic.GetUserId() == player.GetUser()->GetId()) {
                            DB::UserStatistics userStatistic = statistic;
                            if (first) userStatistic.AddWin();
                            else userStatistic.AddGame();
                            storage->GetStorage().update(userStatistic);
                            updated = true;
                            break;
                        }
                    }
                }

                if (!updated) {
                    DB::UserStatistics userStatistic;
                    userStatistic.SetUser(player.GetUser()->GetId());
                    if (first) userStatistic.SetWonGames(1);
                    else userStatistic.SetWonGames(0);
                    userStatistic.SetGameCount(1);
                    storage->Insert(userStatistic);
                }
            }
            res.push_back(crow::json::wvalue{
                {"name", player.GetUser()->GetName()},
                {"score", player.GetScore()}
            });
            first = false;
        }

        m_addedStatisticsInDB = true;
        return crow::json::wvalue{ res };
    });
}


void Server::Backend::GamePowerups(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/game/powerup/chooseAnswer")([&](const crow::request& req)
    {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        m_players[id].DisablePowerup(0);
        m_poweredUpUsers.emplace(id, false);

        srand(time(0));
        std::vector<crow::json::wvalue> answers(4);

        int correctAnswerPosition = rand() % 4;
        int correctAnswer = m_currentQuestion.GetAnswer();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(-correctAnswer, correctAnswer);

        answers[correctAnswerPosition] = correctAnswer;
        for (int i = 0; i < 4; ++i)
            if(i != correctAnswerPosition)
                answers[i] = correctAnswer + distr(gen);

        return crow::response( crow::json::wvalue{ answers } );
    });

    CROW_ROUTE(app, "/game/powerup/suggestAnswer")([&](const crow::request& req)
    {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        m_players[id].DisablePowerup(1);
        m_poweredUpUsers.emplace(id, false);

        int correctAnswer = m_currentQuestion.GetAnswer();
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> distribution(-10, 10);

        return crow::json::wvalue {
            { "answer", correctAnswer + distribution(generator) }
        };
    });

    CROW_ROUTE(app, "/game/powerup/fiftyFifty")([&](const crow::request& req)
    {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        m_players[id].DisablePowerup(2);
        m_poweredUpUsers.emplace(id, false);

        srand(time(0));
        auto choices = storage->GetQuestionChoices<DB::QuestionChoice>(
                m_currentQuestion.GetId());
        auto correctChoice = std::remove_if(choices.begin(), choices.end(),
                                            [&](DB::QuestionChoice &questionChoice)
                                            {
                                                return questionChoice.GetIsCorrect();
                                            });
        choices.erase(choices.begin() + rand() % 2);

        return crow::response(crow::json::wvalue{
                {"choice1", choices[0].GetId()},
                {"choice2", choices[1].GetId()}
        });
    });

    CROW_ROUTE(app, "/game/powerup")([&](const crow::request &req)
    {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;

        const auto& validChoices = m_Map.GetAvailableRegionsForPowerups(id);

        if(validChoices.empty())
            return crow::response(crow::json::wvalue{
                    { "chooseAnswer", false },
                    { "suggestAnswer", false },
                    { "fiftyFifty", false },
            });

        for (const auto& validChoice : validChoices) {
            res.emplace_back(validChoice);
        }

        return crow::response(crow::json::wvalue{
                { "regions", res },
                { "chooseAnswer", m_players[id].GetPowerup(0) },
                { "suggestAnswer", m_players[id].GetPowerup(1) },
                { "fiftyFifty", m_players[id].GetPowerup(2) },
        });
    });

    CROW_ROUTE(app, "/game/powerup").methods("POST"_method)([&](const crow::request &req)
    {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        ChangePlayerStatus(id, Status::InGame);
        m_poweredUpUsers[id] = true;

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        bool poweredupRegionsChosen = true;
        for (const auto &player: m_poweredUpUsers)
        {
           poweredupRegionsChosen = poweredupRegionsChosen && player.second;
        }
        if(poweredupRegionsChosen)
        {
            m_poweredUpUsers.clear();
            GeneratePlayerRanking();
            ChangeAllPlayersStatus(Status::AllPlayersAnswered);
        }

        int selectedRegion = body["region"].i() - 1;
        m_Map.GetRegion(selectedRegion)->DecrementScore();
        m_players[id].DecrementScore();

        return crow::response(200);
    });
}


void Server::Backend::StartDebugEndpoints(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/status")([&]() {
        std::vector<crow::json::wvalue> res_json;

        for (const auto& player : m_players) {
            res_json.push_back(crow::json::wvalue{
                    {"id", player.first},
                    {"name", storage->Get<DB::User>(player.first).GetName()},
                    {"status", ToString(player.second.GetStatus())}
            });
        }

        return crow::json::wvalue{
            { "status", ToString(m_status) },
            { "players", res_json }
        };
    });
}

Server::Backend::Backend()
    :
    m_status(Status::InLobby)
{
    crow::SimpleApp app;

    m_addedStatisticsInDB = false;
    StartDebugEndpoints(app);
    StartLoginRegister(app);
    StartLobby(app);
    StartGame(app);
    GamePowerups(app);

	app.port(18080).multithreaded().run();
}

const std::string Server::Backend::ToString(Status s) {
    switch (s) {
        case Status::InLobby: return "InLobby";
        case Status::BaseChoice: return "BaseChoice";
        case Status::FirstQuestion: return "FirstQuestion";
        case Status::InGame: return "InGame";
        case Status::RegionChoice: return "RegionChoice";
        case Status::RegionQuestion: return "RegionQuestion";
        case Status::PlayersModified: return "PlayersModified";
        case Status::StartNewGame: return "StartNewGame";
        case Status::WaitingForAnswers: return "WaitingForAnswers";
        case Status::MapChanged: return "MapChanged";
        case Status::Answer: return "Answer";
        case Status::AllPlayersAnswered: return "AllPlayersAnswered";
        case Status::Duel: return "Duel";
        case Status::AttackQuestion: return "AttackQuestion";
        case Status::PowerupRegionChoice: return "PowerupRegionChoice";
        case Status::Endgame: return "Endgame";
        default: return "Unknown";
    }
}

const std::unordered_map<int, Server::Player> &Server::Backend::GetPlayers() const {
    return m_players;
}

void Server::Backend::AddPlayer(int id, Status status) {
    int newPlayerId = m_players.size() + 1;
    m_players.insert({id, Player(newPlayerId, id, 0, status)});
}

const DB::Question &Server::Backend::GetCurrentQuestion() const {
    return m_currentQuestion;
}

void Server::Backend::SetNewCurrentQuestion(bool numericOnly) {
    m_playerAnswers.clear();
    m_playerRanking.clear();

    srand(time(0));
    std::vector<DB::Question> questions;
    if (numericOnly) {
        questions = storage->GetNumericQuestions<DB::Question>();
    }
    else {
        questions = DB::DBAccess::GetInstance()->GetAll<DB::Question>();
    }

    int questionsSize = questions.size();
    int randomQuestion = rand() % questionsSize;
    // while random id question was already used find new one
    while (m_usedQuestionIds.find(randomQuestion) != m_usedQuestionIds.end()) {
        randomQuestion = rand() % questionsSize;
    }
    m_currentQuestion = questions[randomQuestion];
    m_usedQuestionIds.insert(randomQuestion);
}

void Server::Backend::GenerateNewMap() {
    int playersNumber = m_players.size();

    switch (playersNumber) {
        case 2:
            m_Map.GenerateTwoPlayerMap();
            break;
        case 3:
            m_Map.GenerateThreePlayerMap();
            break;
        case 4:
            m_Map.GenerateFourPlayerMap();
            break;
    }
}

void Server::Backend::ErasePlayerAnswers() {
    m_playerAnswers.clear();
}

void Server::Backend::AddPlayerAnswer(int id, int answer, int timeRemaining) {
    m_playerAnswers.insert_or_assign(id, std::make_pair(answer, timeRemaining));
}

int Server::Backend::ChangePlayerStatus(int playerId, Status status) {
    auto currentPlayer = m_players.find(playerId);
    if (currentPlayer != m_players.end()) {
        currentPlayer->second.SetStatus(status);
        return 0;
    }
    return -1;
}

int Server::Backend::ChangeAllPlayersStatus(Status status) {
    for (auto & player : m_players)
        player.second.SetStatus(status);
    return 0;
}

void Server::Backend::GeneratePlayerRanking() {
    for (const auto& answer : m_playerAnswers) {
        // playerId, difference, timeRemaining
        if (answer.second.second == -1) // did not answer
            m_playerRanking.emplace_back(answer.first, answer.second.first, answer.second.second); // biggest difference
        else m_playerRanking.emplace_back(answer.first, answer.second.first, answer.second.second); // answer - correctAnswer, time remaining
    }

    if (m_currentQuestion.GetType() == "single_choice") {
        int correctAnswer = m_currentQuestion.GetAnswer();
        std::sort(m_playerRanking.begin(), m_playerRanking.end(),
                  [correctAnswer](const auto &playerAnswer1, const auto &playerAnswer2) {
                      if (std::get<1>(playerAnswer1) != -1 && std::get<1>(playerAnswer2) == -1) // no response
                          return true;
                      if (std::abs(std::get<1>(playerAnswer1) - correctAnswer) <
                          std::abs(std::get<1>(playerAnswer2) - correctAnswer)) // difference
                          return true;
                      return std::abs(std::get<1>(playerAnswer1) - correctAnswer) ==
                             std::abs(std::get<1>(playerAnswer2) - correctAnswer)
                             && std::get<2>(playerAnswer1) > std::get<2>(playerAnswer2); // time
                  });
    }
    else {
        int correctAnswer = DB::DBAccess::GetInstance()->GetCorrectQuestionChoice<DB::QuestionChoice>(
                m_currentQuestion.GetId()).GetId();
        std::sort(m_playerRanking.begin(), m_playerRanking.end(),
                  [correctAnswer](const auto &playerAnswer1, const auto &playerAnswer2) {
                      if (std::get<1>(playerAnswer1) != -1 && std::get<1>(playerAnswer2) == -1) // no response
                          return true;
                      if (std::get<1>(playerAnswer1) == correctAnswer &&
                          std::get<1>(playerAnswer2) != correctAnswer) // difference
                          return true;
                      return std::get<1>(playerAnswer1) == correctAnswer && std::get<1>(playerAnswer2) != correctAnswer
                             && std::get<2>(playerAnswer1) > std::get<2>(playerAnswer2); // time
                  });
    }

}

std::string Server::Backend::GetCorrectAnswerAsString() const {
    if (m_currentQuestion.GetType() == "single_choice") {
        return std::to_string(m_currentQuestion.GetAnswer());
    }
    return storage->GetCorrectQuestionChoice<DB::QuestionChoice>(m_currentQuestion.GetId()).GetChoice();
}

std::string Server::Backend::GetAnswerAsString(int answer) const {
    if (m_currentQuestion.GetType() == "single_choice") {
        return std::to_string(answer);
    }
    return storage->Get<DB::QuestionChoice>(answer).GetChoice();
}

std::vector<Server::Player> Server::Backend::GetOrderedPlayers() const {
    std::vector<Player> res = m_finishedPlayers;
    for (const auto& player : m_players) {
        res.push_back(player.second);
    }

    std::sort(res.begin(), res.end(), [](const auto &playerAnswer1, const auto &playerAnswer2) {
        return playerAnswer1.GetScore() > playerAnswer2.GetScore();
    });

    return res;
}
