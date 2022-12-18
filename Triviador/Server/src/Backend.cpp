#include "Backend.h"
#include "Player.h"
#include "Question.h"
#include "DBAccess.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

Server::Backend::Backend()
    :
    m_status(Backend::Status::InLobby)
{
	crow::SimpleApp app;
    std::vector<Player> playerVector;

	CROW_ROUTE(app, "/lobby")([&]() {
		//wsc.send_binary("HI");
        if (m_status == Status::InLobby ||
            m_status == Status::PlayersModified
            )
            return crow::json::wvalue{
                { "status", ToString(m_status) }
            };
        else return crow::json::wvalue{
                    { "status", ToString(Status::InGame) }
            };
	});

	CROW_ROUTE(app, "/lobby/players")([&]() {
		std::vector<crow::json::wvalue> res_json;

		for (const auto& player : m_players) {
			res_json.push_back(crow::json::wvalue{
				{"id", player.second.GetId()},
				{"name", player.second.GetName()}
			});
		}

		return crow::json::wvalue{
            { "status", ToString(m_status) },
            { "players", res_json }
        };
	});

    CROW_ROUTE(app, "/lobby/join")
        .methods("POST"_method)
        ([&](const crow::request& req) {
            auto body = crow::json::load(req.body);
            auto header = req.get_header_value("ID");
            if (!body)
                return crow::response(400);

            // check if user exists
            int id = std::stoi(header);
            auto player = m_players.find(id);
            if (player != m_players.end())
                return crow::response(400);

            Player newPlayer(body["id"].i(), body["name"].s());
            AddPlayer(id, newPlayer);
            return crow::response(200);
    });

    CROW_ROUTE(app, "/lobby/leave")
        .methods("POST"_method)
        ([&](const crow::request& req) {
            auto header = req.get_header_value("ID");
            int id = std::stoi(header);

            //TODO: put this in a function
            auto player = m_players.find(id);
            if (player == m_players.end())
                return crow::response(400);

            m_players.erase(player);
            return crow::response(200);
    });

    CROW_ROUTE(app, "/game")([&](const crow::request& req) {
        return crow::json::wvalue{
            { "status", ToString(m_status) }
        };
    });

    CROW_ROUTE(app, "/game/start")
        .methods("POST"_method)
        ([&](const crow::request& req) {
            auto header = req.get_header_value("ID");
            int id = std::stoi(header);
            m_status = Status::WaitingForPlayers;
            // add player to player list
            // when all players are in WaitingForPlayers
            // Status becomes InGame

            //TODO: add check if exists

            playerVector.push_back(m_players.at(id)); // make set
            if (playerVector.size() == m_players.size()) {
                m_status = Status::FirstQuestion;
                playerVector.empty();
                SetNewCurrentQuestion();
            }
            return crow::response(200);
    });

    CROW_ROUTE(app, "/game/question/numeric")([&](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);
        //TODO:
//        if (m_status != Status::FirstQuestion && m_status != Status::SecondQuestion)
//            return crow::response(400);

        playerVector.push_back(m_players.at(id));
        if (playerVector.size() == m_players.size()) {
            m_status = Status::WaitingForAnswers;
            playerVector.empty();
            SetNewCurrentQuestion();
        }
        return crow::json::wvalue{
                { "status", ToString(m_status) },
                { "question", m_currentQuestion.GetQuestion() }
        };
    });

    CROW_ROUTE(app, "/game/answer")
        .methods("POST"_method)
        ([&](const crow::request& req) {
            auto header = req.get_header_value("ID");
            int id = std::stoi(header);

            playerVector.push_back(m_players.at(id)); // make set and add pair (ID, answer)
            if (playerVector.size() == m_players.size()) {
                m_status = Status::BaseChoice;
                playerVector.empty();
                SetNewCurrentQuestion();
            }
            return crow::response(200);
    });

//    CROW_ROUTE(app, "/game/start")([&](const crow::request& request) {
//        // TODO: get NUMERIC question from database
//        Server::Question question("Give a close number to 10", false);
//        Server::QuestionChoice<std::variant<int, std::string>> choice(10, true);
//        question.AddChoice(choice);
//        currentQuestion = question;
//
//        auto response = crow::json::wvalue {
//                { "question", question.GetQuestion() }
//        };
//
//        for (const auto& player : lobby.GetPlayers()) {
//            player.second.GetConnection()->send_text(response.dump());
//        }
//
//        // TODO: also return map???
//        return response;
//    });
//
//    CROW_ROUTE(app, "/game/answer").methods("POST"_method)([&](const crow::request& request) {
//        auto json_data = crow::json::load(request.body);
//        answers.emplace_back( json_data["playerId"].i(), json_data["answer"].i() );
//
//        if (answers.size() == lobby.GetPlayers().size()) {
//            currentQuestion.GetBestAnswers(answers);
//            for (int i = 0; i < answers.size(); i++) {
//                lobby.GetPlayers().at(answers[i].first).GetConnection()->send_text("All players answered! You are on the place: " + std::to_string(i));
//            }
//        }
//
//        return crow::response(200);
//    });
	
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
        case Server::Backend::Status::WaitingForPlayers: return "WaitingForPlayers";
        case Server::Backend::Status::WaitingForAnswers: return "WaitingForAnswers";
        default: return "Unknown";
    }
}

const std::unordered_map<int, Server::Player> &Server::Backend::GetPlayers() const {
    return m_players;
}

void Server::Backend::AddPlayer(int id, const Server::Player &player) {
    m_players.insert({ id, player });
}

const Server::Question &Server::Backend::GetCurrentQuestion() const {
    return m_currentQuestion;
}

void Server::Backend::SetNewCurrentQuestion() {
    //TODO: retrieve question from database
    Question currentQuestion("Say a number", false);
    QuestionChoice<std::variant<int, std::string>> choice(10, true);
    currentQuestion.AddChoice(choice);

    m_currentQuestion = currentQuestion;
}
