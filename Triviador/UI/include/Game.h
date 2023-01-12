#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "Region.h"
#include "Tile.h"

class Game
{
public:
    static const int HEIGHT = 112;
    static const int WIDTH = 300;

    void SetNrPlayers(uint8_t nrPlayers);
    uint8_t GetNrPlayers();
    void ReadMap(int id);
    void PrintMap() const;   
    void PrintTiles() const;
    uint8_t getType();
    void setType(uint8_t type);
    std::vector<std::shared_ptr<Region>>getMap();
    std::vector<std::vector<Tile>> getTiles();
    void selectRegions(const std::vector<int>& regions);
    void UpdateMap(const std::vector<Region>& region);

private:
    uint8_t m_nrPlayers=0;
    uint8_t m_type;
    std::vector<std::shared_ptr<Region>> m_map;
    std::vector<std::vector<Tile>> m_tiles;
};
