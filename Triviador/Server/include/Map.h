#ifndef TRIVIADOR_MAP_H
#define TRIVIADOR_MAP_H

#include <memory>
#include <array>
#include <crow.h>

#include "Region.h"

namespace Server {
    class Map { // TODO: make singleton
    public:
        static Map& GetInstance();

        const std::vector<std::shared_ptr<Region>>& GetRegions() const;

        int GetId() const;
        void GenerateTwoPlayerMap();
        void GenerateThreePlayerMap();
        std::vector<int> GetValidBaseChoices() const;
        std::vector<int> GetValidRegionChoices(int userId) const;
        bool AllRegionsOccupied() const;

        Map(Map const&) = delete;
        void operator=(Map const&) = delete;

    private:
        Map() {};

        int m_Id;
        std::vector<std::shared_ptr<Region>> m_Regions;
    };
}

#endif //TRIVIADOR_MAP_H
