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

        AddPlayerAnswer(id, body["answer"].i(), body["timeRemaining"].i());

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
                    {"id", std::get<0>(player)},
                    {"name", storage->Get<DB::User>(std::get<0>(player)).GetName()},
                    {"answer", std::get<1>(player)},
                    {"timeRemaining", std::get<2>(player)}
            });
        }

        // TODO: known bug - if someone calls /game/allAnswers after first base choice.. it fucks up
        bool allPlayersReceived = true;
        switch (m_status) {
            case Status::BaseChoice: /// BASE CHOICE PHASE
                ChangePlayerStatus(id, Status::InGame);
                // wait for all players to turn InGame
                for (const auto& player : m_players)
                    if (player.second != Status::InGame) {
                        allPlayersReceived = false;
                        break;
                    }

                if (allPlayersReceived) // first players chooses base
                    ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::BaseChoice);
                break;

            case Status::RegionChoice: /// REGION CHOICE PHASE
                ChangePlayerStatus(id, Status::InGame);
                // wait for all players to turn InGame
                for (const auto& player : m_players)
                    if (player.second != Status::InGame) {
                        allPlayersReceived = false;
                        break;
                    }

                if (allPlayersReceived) // first players chooses base
                    //TODO: check if all regions are assigned
                    // if not, continue
                    // else start duel
                    // TODO: player chooses n-k regions (n - nr of players, k - position in ranking) !!!!!!!
                    ChangePlayerStatus(std::get<0>(m_playerRanking.front()), Status::RegionChoice);
                break;

            default:
                break;
        }

        return crow::json::wvalue{ {"answers", res} };
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
            ChangeAllPlayersStatus(Status::RegionQuestion); // TODO: must also get map, maybe insert intermediary status
        }
        return crow::response(200);
    });

    CROW_ROUTE(app, "/game/map")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        switch (m_players.find(id)->second) {
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

    CROW_ROUTE(app, "/game/regionChoice")([&](const crow::request& req) {
        return crow::response( 200 );
    });
}

void Server::Backend::StartDebugEndpoints(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/status")([&]() {
        std::vector<crow::json::wvalue> res_json;

        for (const auto& player : m_players) {
            res_json.push_back(crow::json::wvalue{
                    {"id", player.first},
                    {"name", storage->Get<DB::User>(player.first).GetName()},
                    {"status", ToString(player.second)}
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
    m_status(Backend::Status::InLobby)
{
    crow::SimpleApp app;

    StartDebugEndpoints(app);
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
        case Server::Backend::Status::RegionQuestion: return "RegionQuestion";
        case Server::Backend::Status::PlayersModified: return "PlayersModified";
        case Server::Backend::Status::StartNewGame: return "StartNewGame";
        case Server::Backend::Status::WaitingForAnswers: return "WaitingForAnswers";
        case Server::Backend::Status::MapChanged: return "MapChanged";
        case Server::Backend::Status::Answer: return "Answer";
        case Server::Backend::Status::AllPlayersAnswered: return "AllPlayersAnswered";
        case Server::Backend::Status::Duel: return "Duel";
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
    m_playerAnswers.clear();
    m_playerRanking.clear();

    srand(time(0));
    if (numeric) {
        // get all questions and generate random id
        auto questions = storage->GetNumericQuestions<DB::Question>();
        int questionsSize = questions.size();
        int randomQuestion = rand() % questionsSize;
        // while random id question was already used find new one
        while (m_usedQuestionIds.find(randomQuestion) != m_usedQuestionIds.end()) {
            randomQuestion = rand() % questionsSize;
        }
        m_currentQuestion = questions[randomQuestion];
        m_usedQuestionIds.insert(randomQuestion);
    }
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
    for (const auto& answer : m_playerAnswers) {
        // playerId, difference, timeRemaining
        if (answer.second.second == -1) // did not answer
            m_playerRanking.emplace_back(answer.first, INT_MAX, answer.second.second); // biggest difference
        else m_playerRanking.emplace_back(answer.first, answer.second.first, answer.second.second); // answer - correctAnswer, time remaining
    }

    std::sort(m_playerRanking.begin(), m_playerRanking.end(),[correctAnswer](const auto& playerAnswer1, const auto& playerAnswer2) {
        if (std::abs(std::get<1>(playerAnswer1) - correctAnswer) < std::abs(std::get<1>(playerAnswer2) - correctAnswer)) // difference
            return true;
        return std::abs(std::get<1>(playerAnswer1) - correctAnswer) == std::abs(std::get<1>(playerAnswer2) - correctAnswer)
                && std::get<2>(playerAnswer1) > std::get<2>(playerAnswer2); // time
    });

}
