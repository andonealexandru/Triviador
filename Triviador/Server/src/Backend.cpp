#include "Backend.h"
#include "Lobby.h"
#include "Player.h"
#include <crow.h>
#include <iostream>

Server::Backend::Backend()
{
	crow::SimpleApp app;
	Server::Lobby lobby;

	CROW_ROUTE(app, "/")([]() {
		return crow::json::wvalue{ "Hello world!" };
	});

	CROW_ROUTE(app, "/lobby")([&lobby]() {
		std::vector<crow::json::wvalue> res_json;

		const auto& players = lobby.GetPlayers();
		for (const auto& player : players) {
			res_json.push_back(crow::json::wvalue{
				{"id", player.GetId()},
				{"name", player.GetName()}
			});
		}

		return crow::json::wvalue{ res_json };
	});

	CROW_ROUTE(app, "/lobby/add").methods("POST"_method)([&lobby](const crow::request& request) {
		auto req = crow::json::load(request.body);
		if (!req)
			crow::response(400);
		Server::Player player(req["id"].i(), req["name"].s());
		lobby.AddPlayer(player);
		crow::response(200);
		return crow::json::wvalue{ "DONE" };
	});

	app.port(18080).multithreaded().run();

	std::cout << "HI";
}
