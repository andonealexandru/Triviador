#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include "Region.h"
#include "Tile.h"

class Game
{
public:
    void ReadMap();
    void PrintMap() const;   
    void PrintTiles() const;

private:
    uint8_t m_type;
    std::vector<std::shared_ptr<Region>> m_map;
    std::vector<std::vector<Tile>> m_tiles;

public:
    const int HEIGHT = 4;
    const int WIDTH = 3;
};
