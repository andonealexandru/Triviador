#ifndef TRIVIADOR_MAP_H
#define TRIVIADOR_MAP_H

#include <array>
#include <crow.h>

#include "Region.h"

namespace Server {
    class Map {
    public:
        Map() = default;

        std::vector<Region>& GetRegions();

        int GetId();
        void GenerateThreePlayerMap();

    private:
        int m_Id;
        std::vector<Region> m_Regions;
    };
}

#endif //TRIVIADOR_MAP_H
