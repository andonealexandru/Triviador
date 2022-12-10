#include "Backend.h"
#include "Lobby.h"
#include "Player.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>

Server::Backend::Backend()
{
	crow::SimpleApp app;
	std::unordered_set<crow::websocket::connection*> connections;
	std::unordered_map<int, Player> players;
	Server::Lobby lobby;

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
	
	app.port(18080).multithreaded().run();

	std::cout << "HI";
}
