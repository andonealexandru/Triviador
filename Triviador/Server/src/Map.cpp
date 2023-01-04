#include "Map.h"

#include <vector>

Server::Map::Map(int playersNumber) {
    //TODO: change based on player number

    m_Map[0] = {1, 1, 2, 2, 3, 4};
    m_Map[1] = {1, 2, 2, 3, 3, 4};
    m_Map[2] = {1, 1, 5, 3, 4, 4};
    m_Map[3] = {5, 5, 5, 6, 6, 7};
    m_Map[4] = {8, 8, 6, 6, 7, 7};
    m_Map[5] = {8, 8, 8, 7, 7, 7};

}

crow::json::wvalue Server::Map::GetJsonMap() {
    std::vector<crow::json::wvalue> res;

    for (const auto& line : m_Map) {
        std::vector<crow::json::wvalue> temp;
        for (const auto& item : line)
            temp.push_back(crow::json::wvalue{ item });
        res.push_back(crow::json::wvalue{ temp });
    }
    return crow::json::wvalue{ res };
}

Server::Map::Map() {
    m_Map[0] = {1, 1, 2, 2, 3, 4};
    m_Map[1] = {1, 2, 2, 3, 3, 4};
    m_Map[2] = {1, 1, 5, 3, 4, 4};
    m_Map[3] = {5, 5, 5, 6, 6, 7};
    m_Map[4] = {8, 8, 6, 6, 7, 7};
    m_Map[5] = {8, 8, 8, 7, 7, 7};
}
