#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "Region.h"
#include "Tile.h"

class Game
{
public:
    static const int HEIGHT = 100;
    static const int WIDTH = 100;

    void ReadMap();
    void PrintMap() const;   
    void PrintTiles() const;
    uint8_t getType();
    std::vector<std::shared_ptr<Region>>getMap();
    std::vector<std::vector<Tile>> getTiles();

private:
    uint8_t m_type;
    std::vector<std::shared_ptr<Region>> m_map;
    std::vector<std::vector<Tile>> m_tiles;
};
