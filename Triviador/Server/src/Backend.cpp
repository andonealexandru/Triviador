#include "Backend.h"
#include "Player.h"
#include "Question.h"
#include "DBAccess.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>

Server::Backend::Backend()
    :
    m_status(Backend::Status::InLobby)
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/lobby")([&]() {
		//wsc.send_binary("HI");
		return crow::json::wvalue{
            { "status", ToString(m_status) }
        };
	});

	CROW_ROUTE(app, "/lobby/players")([&]() {
		std::vector<crow::json::wvalue> res_json;

		const auto& players = m_players;
		for (const auto& player : players) {
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
        case Server::Backend::Status::BaceChoice: return "BaceChoice";
        case Server::Backend::Status::FirstQuestion: return "FirstQuestion";
        case Server::Backend::Status::InGame: return "InGame";
        case Server::Backend::Status::RegionChoice: return "RegionChoice";
        case Server::Backend::Status::SecondQuestion: return "SecondQuestion";
        default: return "Unknown";
    }
}

const std::unordered_map<int, Server::Player> &Server::Backend::GetPlayers() const {
    return m_players;
}

void Server::Backend::AddPlayer(const Server::Player &player) {
    m_players.insert({ player.GetId(), player });
}
