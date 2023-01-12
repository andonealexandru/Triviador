#include "Region.h"

    Region::Region(int value, int color, int number) :
        m_value(value), m_color(color), m_number(number)
    {
        m_userId = 1;
        m_center = std::make_pair(-1, -1);
        m_isBase = false;
    }

    void Region::SetValue(const int& value)
    {
        m_value = value;
    }

    void Region::SetCenter(const std::pair<int, int>& center)
    {
        m_center = center;
    }

    void Region::SetColor(const int& color)
    {
        m_color = color;
    }

    void Region::SetNumber(const int& number)
    {
        m_number = number;
    }

    void Region::SetHighlight()
    {
        m_highlight = true;
    }

    void Region::SetUserId(int userId)
    {
        m_userId = userId;
    }

    void Region::AddNeighbour(const std::shared_ptr<Region>& region)
    {
        m_neighbours.insert(region);
    }

    void Region::SetBase(const bool& base)
    {
        m_isBase = base;
    }

    int Region::GetValue() const
    {
        return m_value;
    }

    int Region::GetNumber() const
    {
        return m_number;
    }

    std::pair<int, int> Region::GetCenter() const
    {
        return m_center;
    }


    int Region::GetColor() const
    {
        return m_color;
    }

    bool Region::GetHighlight() const
    {
        return m_highlight;
    }

    int Region::GetUserId()
    {
        return m_userId;
    }

    bool Region::IsBase()
    {
        return m_isBase;
    }

    void Region::PrintRegion()
    {
        std::cout << "Numar: " << m_number << "\n";
        std::cout << "Culoare: " << m_color << "\n";
        std::cout << "Centru: " << m_center.first << " " << m_center.second <<"\n";
        std::cout << "Valoare: " << m_value <<"\n";
        std::cout << "Vecini: " << m_neighbours.size() << "\n\n";
    }