#include "Tile.h"

Tile::Tile()
{
	m_coordinates.first = -1;
	m_coordinates.second = -1;
	m_region = nullptr;
}

void Tile::SetTile(const std::pair<int, int>& coordinates,const std::shared_ptr<Region>& region)
{
	m_coordinates = coordinates;
	m_region = region;
}

std::pair<int, int> Tile::GetCoordinate() const
{
	return m_coordinates;
}
