#include "BaseChoiceService.h"

Server::BaseChoiceService::BaseChoiceService(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/game/baseChoice")([](const crow::request& req) {
        auto header = req.get_header_value("ID");
        int id = std::stoi(header);

        std::vector<crow::json::wvalue> res;
        const auto& validChoices = Server::Map::GetInstance().GetValidBaseChoices();

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
}
