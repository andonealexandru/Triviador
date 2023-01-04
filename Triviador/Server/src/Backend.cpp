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
        auto player = m_players.find(id);
        if (player != m_players.end())
            player->second = Status::InLobby;

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

                        // TODO:check if user exists in DB

                        // check if user already in lobby
                        int id = std::stoi(header);
                        auto player = m_players.find(id);
                        if (player != m_players.end())
                            return crow::response(400);

                        // add user in lobby
                        AddPlayer(id, Status::InLobby);
                        // change all other users to playersModified
                        for (auto & player : m_players)
                            player.second = Status::PlayersModified;
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
                        for (auto & player : m_players)
                            player.second = Status::PlayersModified;
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

    CROW_ROUTE(app, "/game/start")
            .methods("POST"_method)
                    ([&](const crow::request& req) {
                        m_status = Status::StartNewGame;

                        for (auto & player : m_players)
                            player.second = Status::StartNewGame;

                        GenerateNewMap(); // TODO

                        return crow::response(200);
                    });

    CROW_ROUTE(app, "/game/map/first")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        auto currentPlayer = m_players.find(id);
        if (currentPlayer != m_players.end())
            currentPlayer->second = Status::InGame;

        bool allGotMap = true;
        for (const auto& player : m_players)
            if (player.second != InGame)
                allGotMap = false;

        if (allGotMap) {
            for (auto &player: m_players)
                player.second = Status::FirstQuestion;
            SetNewCurrentQuestion(true);
        }


        return m_Map.GetJsonMap();
    });

    CROW_ROUTE(app, "/game/firstQuestion")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);



        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "question", m_currentQuestion.GetQuestion() }
        };
    });
//
//    CROW_ROUTE(app, "/game/answer")
//            .methods("POST"_method)
//                    ([&](const crow::request& req) {
//                        auto header = req.get_header_value("ID");
//                        int id = std::stoi(header);
//
//                        playerVector.push_back(m_players.at(id)); // make set and add pair (ID, answer)
//                        if (playerVector.size() == m_players.size()) {
//                            m_status = Status::BaseChoice;
//                            playerVector.empty();
//                            SetNewCurrentQuestion();
//                        }
//                        return crow::response(200);
//                    });

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

    // TODO: initialize map?
}

