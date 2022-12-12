#include "Backend.h"
#include "DBAccess.h"
#include "Lobby.h"
#include "Player.h"
#include "Question.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>

Server::Backend::Backend()
{
//    auto storage = DB::DBAccess::GetInstance()->GetStorage();
    crow::SimpleApp app;
	std::unordered_set<crow::websocket::connection*> connections;
	std::unordered_map<int, Player> players;
	Server::Lobby lobby;

    Server::Question currentQuestion;
    std::vector<std::pair<int, int>> answers;

	CROW_ROUTE(app, "/")([]() {
		//wsc.send_binary("HI");
		return crow::json::wvalue{ "Hello world!" };
	});

	CROW_ROUTE(app, "/lobby/players")([&lobby]() {
		std::vector<crow::json::wvalue> res_json;

		const auto& players = lobby.GetPlayers();
		for (const auto& player : players) {
			res_json.push_back(crow::json::wvalue{
				{"id", player.second.GetId()},
				{"name", player.second.GetName()}
			});
		}

		return crow::json::wvalue{ res_json };
	});

	CROW_ROUTE(app, "/lobby")
		.websocket()
		.onopen([&](crow::websocket::connection& conn) {
			CROW_LOG_INFO << "new websocket connection";
			connections.insert(&conn);
		})
		.onclose([&](crow::websocket::connection& conn, const std::string& reason) {
			CROW_LOG_INFO << "websocket connection closed: " << reason;
			connections.erase(&conn);
		})
		.onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
			auto json_data = crow::json::load(data);
			std::string status = json_data["status"].s();
			if (status == "updatePlayer") {
				Server::Player currentPlayer(json_data["id"].i(), json_data["name"].s(), &conn);
				// TODO: check if player is already in lobby
				lobby.AddPlayer(currentPlayer);
				for (const auto& x : lobby.GetPlayers()) {
					x.second.GetConnection()->send_text("User " + currentPlayer.GetName() + " joined!");
				}
			}
		});

    CROW_ROUTE(app, "/game/start")([&](const crow::request& request) {
        // TODO: get NUMERIC question from database
        Server::Question question("Give a close number to 10", false);
        Server::QuestionChoice<std::variant<int, std::string>> choice(10, true);
        question.AddChoice(choice);
        currentQuestion = question;

        auto response = crow::json::wvalue {
                { "question", question.GetQuestion() }
        };

        for (const auto& player : lobby.GetPlayers()) {
            player.second.GetConnection()->send_text(response.dump());
        }

        // TODO: also return map???
        return response;
    });

    CROW_ROUTE(app, "/game/answer").methods("POST"_method)([&](const crow::request& request) {
        auto json_data = crow::json::load(request.body);
        answers.emplace_back( json_data["playerId"].i(), json_data["answer"].i() );

        if (answers.size() == lobby.GetPlayers().size()) {
            currentQuestion.GetBestAnswers(answers);
            for (int i = 0; i < answers.size(); i++) {
                lobby.GetPlayers().at(answers[i].first).GetConnection()->send_text("All players answered! You are on the place: " + std::to_string(i));
            }
        }

        return crow::response(200);
    });
	
	app.port(18080).multithreaded().run();

	std::cout << "HI";
}
