#include "Region.h"

namespace DB
{
    Region::Region(std::vector<std::pair<int, int>> tiles, int value, std::pair<int, int> center, std::string color, std::vector<Region*> neighbours) :
        m_tiles{ tiles }, m_value{ value }, m_center{ center }, m_color{ color }, m_neighbours{ neighbours }
    {
    }

    void Region::SetTitles(std::vector<std::pair<int, int>> tiles)
    {
        m_tiles = tiles;
    }

    void Region::SetValue(int value)
    {
        m_value = value;
    }

    void Region::SetCenter(std::pair<int, int> center)
    {
        m_center = center;
    }

    void Region::SetColor(std::string color)
    {
        m_color = color;
    }

    void Region::SetNeighbours(std::vector<Region*> neighbours)
    {
        m_neighbours = neighbours;
    }

    std::vector<std::pair<int, int>> Region::GetTiles() const
    {
        return m_tiles;
    }

    int Region::GetValue() const
    {
        return m_value;
    }

    std::pair<int, int> Region::GetCenter() const
    {
        return m_center;
    }

    std::string Region::GetColor() const
    {
        return m_color;
    }

    std::vector<Region*> Region::GetNeighbours() const
    {
        return m_neighbours;
    }
}