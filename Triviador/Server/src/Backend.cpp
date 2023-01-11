#include "Backend.h"
#include "Player.h"
#include "Question.h"
#include "DBAccess.h"
#include "User.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

auto storage = DB::DBAccess::GetInstance(); // TODO: get rid of this

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

    // TODO: add /users/get
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
                {"status", m_players.find(id) == m_players.end() ? ToString(m_status) : ToString(m_players.find(id)->second)}
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
                    {"name", storage->Get<DB::User>(player.first).GetName()}
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

                        // TODO:check if user exists in DB

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
                 m_players.find(id) == m_players.end() ? ToString(m_status) : ToString(m_players.find(id)->second)}
        };
    });

    CROW_ROUTE(app, "/game/players")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res_json;

        for (const auto& player : m_players) {
            res_json.push_back(crow::json::wvalue{
                    {"id", player.first},
                    {"name", storage->Get<DB::User>(player.first).GetName()}
            });
        }

        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "players", res_json }
        };
    });

    CROW_ROUTE(app, "/game/start")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        m_status = Status::StartNewGame;
                        ChangeAllPlayersStatus(Status::StartNewGame);

                        GenerateNewMap(); // TODO

                        return crow::response(200);
                    });

    CROW_ROUTE(app, "/game/map/first")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::InGame);

        bool allGotMap = true;
        for (const auto& player : m_players)
            if (player.second != InGame)
                allGotMap = false;

        if (allGotMap) {
            ChangeAllPlayersStatus(Status::FirstQuestion);
            SetNewCurrentQuestion(true);
        }

        return crow::json::wvalue{ {"mapId", m_Map.GetId()} };
    });

    CROW_ROUTE(app, "/game/firstQuestion")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        ChangePlayerStatus(id, Status::Answer);
        m_status = Status::BaseChoice;

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

        if (body["answer"].t() != crow::json::type::String)
            AddPlayerAnswer(id, body["answer"].i(), body["timeRemaining"].i());
        else AddPlayerAnswer(id, -1, 0);

        if (m_playerAnswers.size() == m_players.size()) {
            GeneratePlayerRanking();
            ChangeAllPlayersStatus(Status::AllPlayersAnswered);
        }

        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/allAnswers")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;

        for (const auto& player : m_playerRanking) {
            res.push_back(crow::json::wvalue{
                    {"id", player}
            });
        }

        switch (m_status) {
            case Status::BaseChoice:
                ChangePlayerStatus(m_playerRanking.front(), Status::BaseChoice); // first players chooses base
            default:
                break;
        }

        return crow::json::wvalue{ res };
    });

    CROW_ROUTE(app, "/game/baseChoice").methods("POST"_method)([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400);

        m_Map.GetRegions()[body["base"].i() - 1].MakeBase();
        m_Map.GetRegions()[body["base"].i() - 1].SetUserId(id);

        // all players need to update map
        ChangeAllPlayersStatus(Status::MapChanged);

        // erase first player from list
        if (!m_playerRanking.empty())
            m_playerRanking.erase(m_playerRanking.cbegin());

        if (!m_playerRanking.empty())
            ChangePlayerStatus(m_playerRanking.front(), Status::BaseChoice);
        else {// all players have base, starting RegionChoice
            m_status = Status::RegionChoice;
            ChangeAllPlayersStatus(Status::SecondQuestion); // TODO: must also get map, maybe insert intermediary status
        }
        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/map")([&](const crow::request& req) {
        std::vector<crow::json::wvalue> res;

        for (const auto& region : m_Map.GetRegions()) {
            res.push_back(crow::json::wvalue{
                    { "id", region.GetId() },
                    { "userId", region.GetUserId() },
                    { "isBase", region.IsBase() }
            });
        }

        return crow::json::wvalue{ res };
    });
    //TODO: afer seing all results change to InGame
    //TODO: afer seing map change to InGame
}

Server::Backend::Backend()
    :
    m_status(Backend::Status::InLobby)
{
	crow::SimpleApp app;

    StartLoginRegister(app);
    StartLobby(app);
    StartGame(app);
	
	app.port(18080).multithreaded().run();
}

const std::string Server::Backend::ToString(Server::Backend::Status s) {
    switch (s) {
        case Server::Backend::Status::InLobby: return "InLobby";
        case Server::Backend::Status::BaseChoice: return "BaseChoice";
        case Server::Backend::Status::FirstQuestion: return "FirstQuestion";
        case Server::Backend::Status::InGame: return "InGame";
        case Server::Backend::Status::RegionChoice: return "RegionChoice";
        case Server::Backend::Status::SecondQuestion: return "SecondQuestion";
        case Server::Backend::Status::PlayersModified: return "PlayersModified";
        case Server::Backend::Status::StartNewGame: return "StartNewGame";
        case Server::Backend::Status::WaitingForAnswers: return "WaitingForAnswers";
        case Server::Backend::Status::MapChanged: return "MapChanged";
        case Server::Backend::Status::Answer: return "Answer";
        case Server::Backend::Status::AllPlayersAnswered: return "AllPlayersAnswered";
        default: return "Unknown";
    }
}

const std::unordered_map<int, Server::Backend::Status> &Server::Backend::GetPlayers() const {
    return m_players;
}

void Server::Backend::AddPlayer(int id, Server::Backend::Status status) {
    m_players.insert({id, status});
}

const DB::Question &Server::Backend::GetCurrentQuestion() const {
    return m_currentQuestion;
}

void Server::Backend::SetNewCurrentQuestion(bool numeric) {
    if (numeric) {
        auto questions = storage->GetNumericQuestions<DB::Question>();
        m_currentQuestion = questions.front();
    }
}

void Server::Backend::GenerateNewMap() {
    int playersNumber = m_players.size();

    switch (playersNumber) {
        case 2:
            break;
        case 3:
            m_Map.GenerateThreePlayerMap();
            break;
        case 4:
            break;
    }
}

void Server::Backend::ErasePlayerAnswers() {
    m_playerAnswers.clear();
}

void Server::Backend::AddPlayerAnswer(int id, int answer, int timeRemaining) {
    m_playerAnswers.insert_or_assign(id, std::make_pair(answer, timeRemaining));
}

int Server::Backend::ChangePlayerStatus(int playerId, Server::Backend::Status status) {
    auto currentPlayer = m_players.find(playerId);
    if (currentPlayer != m_players.end()) {
        currentPlayer->second = status;
        return 0;
    }
    return -1;
}

int Server::Backend::ChangeAllPlayersStatus(Server::Backend::Status status) {
    for (auto & player : m_players)
        player.second = status;
    return 0;
}

void Server::Backend::GeneratePlayerRanking() {
    // get correct answer
    int correctAnswer = m_currentQuestion.GetAnswer();
    std::vector<std::pair<int, int>> differences;
    for (const auto& answer : m_playerAnswers) {
        m_playerRanking.push_back(answer.first); // player id
        if (answer.second.first == -1) // did not answer
            differences.push_back(std::make_pair(INT_MAX, answer.second.second)); // biggest difference
        else differences.push_back(std::make_pair(abs(answer.second.first - correctAnswer),
                                                  answer.second.second)); // answer - correctAnswer, time remaining
    }
    // sort
    for (int i = 0; i < differences.size() - 1; ++i) {
        for (int j = i+1; j < differences.size(); ++j) {
            if (differences[i].first > differences[j].first) {
                std::swap(differences[i], differences[j]);
                std::swap(m_playerRanking[i], m_playerRanking[j]);
            }
            else if (differences[i].first == differences[j].first && differences[i].second < differences[j].second) {
                std::swap(differences[i], differences[j]);
                std::swap(m_playerRanking[i], m_playerRanking[j]);
            }
        }
    }
}
