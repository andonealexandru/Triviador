#ifndef TRIVIADOR_MAP_H
#define TRIVIADOR_MAP_H

#include <array>
#include <crow.h>

namespace Server {
    class Map {
    public:
        Map();
        Map(int playersNumber);

        crow::json::wvalue GetJsonMap();

    private:
        std::array<std::array<int, 6>, 6> m_Map;
    };
}

#endif //TRIVIADOR_MAP_H
